//testconsept
{% verbatim %}
var handlebars_nav_menu ='{{#each files}}{{#ifCond type \'==\' \'dir\'}}       <li class="">       <a href=\"#\" onclick=\"session.getDirectoryListing(\'{{path}}\', procDirectoryListing);\"><i class=\"fa fa-lg fa-fw fa-folder-o\"></i> <span class=\"menu-item-parent\">{{name}}</span></a>       <ul data-path=\'{{path}}\'>       </ul>       </li>       {{else}}       {{#ifCond ext \'==\' \'jade\'}}       <li><a href=\"{{url}}\" title=\"{{name}}\"><i class=\"fa icon-html\"></i>{{name}}</a></li>       {{/ifCond}}       {{#ifCond ext \'==\' \'pug\'}}       <li><a href=\"{{url}}\" title=\"{{name}}\"><i class=\"fa icon-html\"></i>{{name}}</a></li>       {{/ifCond}}       {{#ifCond ext \'==\' \'html\'}}       <li><a href=\"{{url}}\" title=\"{{name}}\"><i class=\"fa icon-html\"></i>{{name}}</a></li>       {{/ifCond}}       {{#ifCond ext \'==\' \'js\'}}       <li><a href=\"{{url}}\" title=\"{{name}}\"><i class=\"fa icon-javascript-alt\"></i>{{name}}</a></li>       {{/ifCond}}       {{#ifCond ext \'==\' \'py\'}}       <li><a href=\"{{url}}\" title=\"{{name}}\"><i class=\"fa icon-python-alt\"></i>{{name}}</a></li>       {{/ifCond}}       {{#ifCond ext \'==\' \'pyc\'}}       <li><a href=\"{{url}}\" title=\"{{name}}\"><i class=\"fa icon-python-alt\"></i>{{name}}</a></li>       {{/ifCond}}       {{/ifCond}}       {{/each}}';

{% endverbatim %}
var instance = new PrioritySocket('data','getInstances',callbacktest);
instance.SocketPull();
    function callbacktest(message){
    instances = JSON.parse(message.data);
    $("#yamcs-instance-list").text('');
    $.each(instances.instance, function (i, selected) {
    $("#yamcs-instance-list").append(
    $('<li>').append(
    $('<a>').attr('href', 'javascript:void(0);').on("click", function (item) {
    var newInstance = item.target.text;
    $("#yamcs-instance-selected").text(newInstance);
    //session.setDefaultInstance(newInstance, function () {
    //  BindHtmlToCommanderInstance(newInstance);});
    }).append(selected.name)));
    });
    getWorkspaceDir('');
    }


    var procDirectoryListing = function (listing) {
    listing = JSON.parse(listing.data);
    console.log(listing);
    // Add 'url', and 'ext' attributes
    for (var i = 0; i < listing.files.length; i++) {
    var path = listing.files[i].path;
    var subpath;
    var subname;
    var ext;
    var name = listing.files[i].name;
    subpath = path.substring(0, path.lastIndexOf("/") + 1);
    var a = listing.files[i].path.split('.');
    if (a.length === 1 || ( a[0] === '' && a.length === 2 )) {
    ext = '';
    }
    ext = a.pop();
    /* Prepend 'view' to the path to make the URL and cut off the jade extension. */
    if (ext == '') {
    listing.files[i].url = 'view' + path;
    } else {
    if (ext == 'js') {
    listing.files[i].url = 'view/scripting/index?url=ws' + path;
    } else {
    listing.files[i].url = 'view' + path;
    }
    }
    listing.files[i].ext = ext;
    }
    updateNavBar(listing);
    //addNavMenu();
    };



    function getWorkspaceDir(s){
    var commands = new PrioritySocket('dir',s,procDirectoryListing);
    commands.SocketPull();
    };



    function getNavEntry(path){
    return $( "nav" ).find( "ul[data-path='" + path + "']" );
    };

    function updateNavBar(listing) {
    var source = $.trim($('#navBarTemplate').html());
    var source =handlebars_nav_menu;
    console.log(source);
    var template = Handlebars.compile(source);
    var html = template(listing);
    var tgtObj = getNavEntry(listing.path);
    //console.log(tgtObj.html(''));
    tgtObj.html('');
    //console.log(tgtObj.html(''));
    tgtObj.append(html);
    //console.log(tgtObj.append(html));
    //tgtObj.removeClass('jarvis-menu-applied');
    //console.log(tgtObj.removeClass('jarvis-menu-applied'));
    //initApp.leftNav();
    };
    function addNavMenu() {
    var menu = new BootstrapMenu('#left-panel', {
    fetchElementData: function($rowElem) {
    },
    actionsGroups: [
    ['newFolder', 'newDisplay', 'newScriptJS', 'newScriptPy' ],
    ['openFile', 'editFile'],
    ['copyFile', 'pasteFile', 'deleteFile', 'renameFile', 'moveFile']
    ],
    actions: {
    newFolder: {
    name: 'New Folder',
    iconClass: 'fa-folder-o',
    onClick: function() {
    console.log("'New Folder' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    },
    newDisplay: {
    name: 'New Display',
    iconClass: 'fa-tachometer',
    onClick: function() {
    console.log("'New Display' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    },
    newScriptJS: {
    name: 'New JS Script',
    iconClass: 'icon-javascript',
    onClick: function() {
    console.log("'New JS Script' clicked.");
    },
    isShown: function() {
    return true;
    }
    },
    newScriptPy: {
    name: 'New Py Script',
    iconClass: 'icon-python',
    onClick: function() {
    console.log("'New Py Script' clicked.");
    },
    isShown: function() {
    return true;
    }
    },
    openFile: {
    name: 'Open',
    iconClass: 'fa-eye',
    onClick: function() {
    console.log("'Open' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    },
    editFile: {
    name: 'Edit',
    iconClass: 'fa-edit',
    onClick: function() {
    console.log("'Edit' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    },
    copyFile: {
    name: 'Copy',
    iconClass: 'fa-copy',
    onClick: function() {
    console.log("'Copy' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    },
    pasteFile: {
    name: 'Paste',
    iconClass: 'fa-paste',
    onClick: function() {
    console.log("'Paste' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    },
    deleteFile: {
    name: 'Delete',
    iconClass: 'fa-trash',
    onClick: function() {
    console.log("'Delete' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    },
    renameFile: {
    name: 'Rename',
    onClick: function() {
    console.log("'Rename' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    },
    moveFile: {
    name: 'Move',
    onClick: function() {
    console.log("'Move' clicked.");
    },
    isEnabled: function() {
    return true;
    }
    }
    }
    });
    };

