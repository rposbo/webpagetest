<meta http-equiv="Content-type" content="text/html;charset=UTF-8">
<?php
// Copyright 2020 Catchpoint Systems Inc.
// Use of this source code is governed by the Polyform Shield 1.0.0 license that can be
// found in the LICENSE.md file.
if( count($page_keywords) )
    echo '<meta name="keywords" content="' . implode(',', $page_keywords) . "\">\n";  //"
if( strlen($page_description) )
    echo "<meta name=\"description\" content=\"$page_description\">\n";
?>
<meta name="author" content="Patrick Meenan">
<meta http-equiv="X-UA-Compatible" content="IE=Edge"> 

<link rel="apple-touch-icon" sizes="180x180" href="/images/favicon/apple-touch-icon.png">
<link rel="icon" type="image/png" sizes="32x32" href="/images/favicon/favicon-32x32.png">
<link rel="icon" type="image/png" sizes="16x16" href="/images/favicon/favicon-16x16.png">
<link rel="mask-icon" href="/images/favicon/safari-pinned-tab.svg" color="#5bbad5">
<link rel="shortcut icon" href="/images/favicon/favicon.ico">

<?php 
    if(!isset($noanalytics) && extension_loaded('newrelic'))
        echo @newrelic_get_browser_timing_header();
    if (file_exists('./settings/server/customhead.inc.php')) {
        include('./settings/server/customhead.inc.php');
    } elseif (file_exists('./settings/common/customhead.inc.php')) {
        include('./settings/common/customhead.inc.php');
    } elseif (file_exists('./settings/customhead.inc.php')) {
        include('./settings/customhead.inc.php');
    }
    echo "<script type=\"text/javascript\">\n";
    if (is_file('./js/user-timing-min.js'))
      include('./js/user-timing-min.js');
    if (!isset($noanalytics) && is_file('./js/user-timing-rum-min.js'))
      include('./js/user-timing-rum-min.js');
    echo "\n</script>\n";
    $cssName = GetSetting('newUI') ? 'pagestyle2' : 'pagestyle';
    echo "<link rel=\"stylesheet\" href=\"{$GLOBALS['cdnPath']}/$cssName.css?v=" . VER_CSS . "\" type=\"text/css\">\n";
    echo "<style type=\"text/css\">\n";
    
    // switch to the private install logo if we're not running on webpagetest
    $privateInstall = true;
    if( stristr($_SERVER['HTTP_HOST'] , 'webpagetest.org') !== false )
        $privateInstall = false;

    $blkLogo = false;
    if (isset($_REQUEST['color'])) {
        $color = html2rgb($_REQUEST['color']);
        if ($color) {
            echo "body {background-color: #{$_REQUEST['color']};}";
            $max = max($color[0], $color[1], $color[2]);
            if( $max >= 192 )
                $blkLogo = true;
        }
    }
            
    if( $privateInstall )
    {
        if( $blkLogo )
            echo ".logo a {background-image: url(/images/logo_private_blk.png);}";
        else
            echo ".logo a {background-image: url(/images/logo_private.png);}";
    }
    elseif( $blkLogo )
    {
        echo ".logo a {background-image: url(/images/logo_blk.png);}";
    }

    // include a custom style if one exists
    if( is_file('./settings/custom.css') )
        include('./settings/custom.css');

    echo "\n</style>\n";
        
    // include the analytics code if it is appropriate
    if (!isset($noanalytics))
        include('analytics.inc');
        
?>
