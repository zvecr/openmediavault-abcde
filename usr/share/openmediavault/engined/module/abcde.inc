<?php
require_once "openmediavault/config.inc";
require_once "openmediavault/error.inc";
require_once "openmediavault/initscript.inc";
require_once "openmediavault/module.inc";
require_once "openmediavault/util.inc";
class OMVModuleABCDE extends OMVModuleServiceAbstract implements
	OMVINotifyListener,
	OMVIModuleServiceStatus
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
	 * Get the module status.
	 */
	public function getStatus()
	{
		global $xmlConfig;

		// Get the configuration object.
		$object = $xmlConfig->get($this->getXPath());
		if (is_null($object)) {
			throw new OMVException(
				OMVErrorMsg::E_CONFIG_GET_OBJECT_FAILED,
				$this->getXPath()
			);
		}
		
		// Return the status of the service. This information is displayed
		// under Diagnostics/Services.
		return array(
			"name" => $this->getName(),
			"title" => gettext("ABCDE"),
			"enabled" => boolval($object["enable"]),
			"running" => boolval($object["enable"])
		);
	}

	/**
	 * Generate the configuration. 
	 */
	public function applyConfig()
	{
		global $xmlConfig;
		$cmd = sprintf("omv-mkconf %s 2>&1", $this->getName());
		if (0 !== $this->exec($cmd, $output)) {
			throw new OMVException(
				OMVErrorMsg::E_EXEC_FAILED,
				$cmd,
				implode("\n", $output)
			);
		}
	}

	/**
	 * Bind listeners.
	 */
	public function bindListeners(OMVNotifyDispatcher $dispatcher)
	{
		$moduleMgr = &OMVModuleMgr::getInstance();
		
		// Add listeners
		$dispatcher->addListener(
			OMV_NOTIFY_MODIFY,
			$this->getEventMessagePath(),
			array($this, "setDirty")
		);
	}
}
// Register module
$moduleMgr = &OMVModuleMgr::getInstance();
$moduleMgr->registerModule(new OMVModuleABCDE());