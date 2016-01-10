<?php
require_once("openmediavault/config.inc");
require_once("openmediavault/error.inc");
require_once("openmediavault/notify.inc");
require_once("openmediavault/object.inc");
require_once("openmediavault/rpcservice.inc");
require_once("openmediavault/util.inc");
class OMVRpcServiceABCDE extends OMVRpcServiceAbstract
{
    /**
     * Get the main event message path of the service. This is a helper 
     * function to avoid "magic numbers".
     *
     * @return string
     */
    private function getEventMessagePath()
    {
        return sprintf("org.openmediavault.services.%s", $this->getName());
    }
    
    /**
     * Get the base XPath of the service. This is a helper function to avoid 
     * "magic numbers".
     *
     * @return string
     */
    private function getXpath()
    {
        return sprintf("/config/services/%s", $this->getName());
    }

    /**
     * Get the name of the RPC service.
     *
     * @return string
     */
    public function getName()
    {
        return "abcde";
    }

    /**
     * Initialize the RPC service. The RPC methods are registered in this
     * function with $this->registerMethod.
     *
     * @return void
     */
    public function initialize()
    {
        $this->registerMethod("getSettings");
        $this->registerMethod("setSettings");
    }

    /**
     * Gets config as a map of key value pairs
     *
     * @return object
     */
    public function getSettings($params, $context)
    {
        global $xmlConfig;

        // Validate the RPC caller context.
        $this->validateMethodContext($context, array(
            "role" => OMV_ROLE_ADMINISTRATOR
        ));
        
        // Get the configuration object.
        $object = $xmlConfig->get($this->getXpath());
        
        // If no data was found, throw an exception and provide the XPath that failed.
        if (is_null($object)) {
            throw new OMVException(
                OMVErrorMsg::E_CONFIG_GET_OBJECT_FAILED,
                $this->getXpath()
            );
        }
        
        // Modify result data.
        $object["enable"] = boolval($object["enable"]);
        $object["directory"] = $object["directory"];
        $object["owner"] = $object["owner"];
        $object["format"] = $object["format"];
        $object["quality"] = $object["quality"];
        $object["name_format"] = $object["name_format"];
        $object["generate_playlist"] = boolval($object["generate_playlist"]);
        $object["encoder_count"] = intval($object["encoder_count"]);
        
        return $object;
    }

    /**
     * Sets config via a map of key value pairs
     *
     * @return object
     */
    public function setSettings($params, $context)
    {
        global $xmlConfig;
        
        $this->validateMethodContext($context, array(
            "role" => OMV_ROLE_ADMINISTRATOR
        ));

        $this->validateMethodParams(
            $params,
            '{
                "type": "object",
                "properties": {
                    "enable"            : { "type": "boolean" },
                    "directory"         : { '.$GLOBALS["OMV_JSONSCHEMA_UUID"].' },
                    "owner"             : { "type": "string" },
                    "format"            : { "type": "string", "enum":["mp3", "flac"]},
                    "quality"           : { "type": "integer", "enum":[0,1,2,3,4,5,6,7,8] },
                    "name_format"       : { "type": "string" },
                    "generate_playlist" : { "type": "boolean" },
                    "encoder_count"     : { "type": "integer", "enum":[1,2,3,4,5,6,7,8] }
                }
            }'
        );

        // Update the configuration object.
        $object = array(
            "enable" => array_boolval($params, "enable"),
            "directory" => $params["directory"],
            "owner" => $params["owner"],
            "format" => $params["format"],
            "quality" => $params["quality"],
            "name_format" => $params["name_format"],
            "generate_playlist" => array_boolval($params, "generate_playlist"),
            "encoder_count" => $params["encoder_count"],
        );
        
        // Update the configuration file. If it fails it throws an exception.
        if (false === $xmlConfig->replace($this->getXpath(), $object)) {
            throw new OMVException(
                OMVErrorMsg::E_CONFIG_SET_OBJECT_FAILED,
                $this->getXpath()
            );
        }
        
        // Notify configuration changes.
        $dispatcher = &OMVNotifyDispatcher::getInstance();
        $dispatcher->notify(
            OMV_NOTIFY_MODIFY,
            $this->getEventMessagePath(),
            $object
        );
        return $object;
    }
}
// Register the RPC service.
$rpcServiceMgr = &OMVRpcServiceMgr::getInstance();
$rpcServiceMgr->registerService(new OMVRpcServiceABCDE());