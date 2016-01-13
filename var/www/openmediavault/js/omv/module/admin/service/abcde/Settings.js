// require("js/omv/WorkspaceManager.js")
// require("js/omv/workspace/form/Panel.js")
// require("js/omv/workspace/window/Form.js")
// require("js/omv/data/Store.js")
// require("js/omv/data/Model.js")
// require("js/omv/data/proxy/Rpc.js")
// require("js/omv/workspace/window/plugin/ConfigObject.js")
// require("js/omv/form/field/SharedFolderComboBox.js")
// require("js/omv/form/field/UserComboBox.js")
Ext.define("OMV.module.admin.service.abcde.Settings", {
    extend: "OMV.workspace.form.Panel",
    requires : [
        "OMV.form.field.SharedFolderComboBox",
        "OMV.form.field.UserComboBox"
    ],
    rpcService: "abcde",
    rpcGetMethod: "getSettings",
    rpcSetMethod: "setSettings",

    getFormItems: function() {
        return [{
            xtype: "fieldset",
            title: _("General settings"),
            fieldDefaults: {
                labelSeparator: ""
            },
            items: [{
                xtype: "checkbox",
                name: "enable",
                fieldLabel: _("Enable"),
                checked: false
            },
            {
                xtype      : "sharedfoldercombo",
                name       : "directory",
                fieldLabel : _("Directory"),
                allowBlank: false,
				plugins: [{
					ptype: "fieldinfo",
					text: _("Folder to store ripped audio files")
				}]
            },
            {
                xtype      : "usercombo",
                name       : "owner",
                fieldLabel : _("Owner"),
                value      : "nobody",
                userType   : "normal",
                allowBlank: false,
				plugins: [{
					ptype: "fieldinfo",
					text: _("User to own the ripped audio files")
				}]
            },
            {
				xtype: "combo",
				name: "format",
				fieldLabel: _("Format"),
				queryMode: "local",
				store: Ext.create("Ext.data.ArrayStore", {
					fields: [ "value", "text" ],
					data: [
						[ "mp3", "MP3" ],
						[ "flac", "FLAC" ]
					]
				}),
				displayField: "text",
				valueField: "value",
				allowBlank: false,
				editable: false,
				triggerAction: "all",
				value: "mp3",
				plugins: [{
					ptype: "fieldinfo",
					text: _("Output format")
				}]
			},
            {
				xtype: "combo",
				name: "quality",
				fieldLabel: _("Quality"),
				queryMode: "local",
				store: Ext.create("Ext.data.ArrayStore", {
					fields: [ "value", "text" ],
					data: [
						[ 0, "0 - smallest file size" ],
						[ 1, "1" ],
                        [ 2, "2" ],
                        [ 3, "3" ],
						[ 4, "4" ],
                        [ 5, "5" ],
						[ 6, "6" ],
                        [ 7, "7" ],
						[ 8, "8 - best quality" ]
					]
				}),
				displayField: "text",
				valueField: "value",
				allowBlank: false,
				editable: false,
				triggerAction: "all",
				value: 5,
				plugins: [{
					ptype: "fieldinfo",
					text: _("Set output audio quality and file size")
				}]
			},
            {
				xtype: "combo",
				name: "name_format",
				fieldLabel: _("Track name format"),
				queryMode: "local",
				store: Ext.create("Ext.data.ArrayStore", {
					fields: [ "value" ],
					data: [
						[ "${ARTISTFILE}/${ALBUMFILE}/${TRACKNUM} - ${TRACKFILE}" ],
                        [ "${ARTISTFILE}/${ALBUMFILE}/${TRACKNUM}_${TRACKFILE}" ],
						[ "${ARTISTFILE}-${ALBUMFILE}/${TRACKNUM}.${TRACKFILE}" ]
					]
				}),
				displayField: "value",
				valueField: "value",
				allowBlank: false,
				editable: true,
				triggerAction: "all",
				value: "${ARTISTFILE}/${ALBUMFILE}/${TRACKNUM} - ${TRACKFILE}",
				plugins: [{
					ptype: "fieldinfo",
					text: _("Track output filename format, available tokens : GENRE, ALBUMFILE, ARTISTFILE, TRACKFILE, TRACKNUM, YEAR")
				}]
			},
            {
                xtype: "checkbox",
                name: "generate_playlist",
                fieldLabel: _("Generate Playlist"),
                checked: false,
				plugins: [{
					ptype: "fieldinfo",
					text: _("Generate m3u playlists for ripped albums")
				}]
            }]
        },
        {
			xtype: "fieldset",
			title: _("Advanced settings"),
			fieldDefaults: {
				labelSeparator: ""
			},
			items: [{
				xtype: "combo",
				name: "encoder_count",
				fieldLabel: _("Encoder Count"),
				queryMode: "local",
				store: Ext.create("Ext.data.ArrayStore", {
					fields: [ "value", "text" ],
					data: [
						[ 1, "1" ],
						[ 2, "2" ],
                        [ 3, "3" ],
						[ 4, "4" ],
                        [ 5, "5" ],
						[ 6, "6" ],
                        [ 7, "7" ],
						[ 8, "8" ]
					]
				}),
				displayField: "text",
				valueField: "value",
				allowBlank: false,
				editable: false,
				triggerAction: "all",
				value: 2,
				plugins: [{
					ptype: "fieldinfo",
					text: _("Count of how many encoders to run simultaneously")
				}]
			},
            {
                xtype: "textfield",
                name: "extra_options",
                fieldLabel: _("Extra options"),
				allowBlank: true,
				plugins: [{
					ptype: "fieldinfo",
					text: _("Extra options to pass to abcde, see http://linux.die.net/man/1/abcde")
				}]
            }]
        }];
    }
});

OMV.WorkspaceManager.registerPanel({
    id: "settings", 
    path: "/service/abcde", 
    text: _("Settings"), 
    position: 10,
    className: "OMV.module.admin.service.abcde.Settings" 
});