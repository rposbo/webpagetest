            <div style="width:100%;float:none;clear:both;"></div>

            <?php
            //If we're looking at a test result, include the inner test-result div
            if( !strcasecmp('Test Result', $tab) && (!isset($nosubheader) || !@$nosubheader) )
            {
                echo '</div></div>';
            }
            ?>
            </div>
        </div>
    </div>
</div>

<div class="page">
    <?php
        $feeds = null;
        if( is_file('./tmp/feeds.dat') )
            $feeds = json_decode(file_get_contents('./tmp/feeds.dat'), true);

        if( isset($feeds) && count($feeds) && !defined('BARE_UI') )
        {
            echo '<table id="feeds"><tr>';

            // display the column headers
            foreach( $feeds as $title => &$feed )
                echo "<th>$title</th>";
            echo '</tr><tr>';

            // display the feed contents
            $column = 0;
            foreach( $feeds as $title => &$feed )
            {
                $column++;
                echo '<td><ul>';

                // keep a list of titles so we only display the most recent (for threads)
                $titles = array();

                $count = 0;
                $extended = false;
                foreach( $feed as $time => &$item )
                {
                    if( $count <= 25 )
                    {
                        $dupe = false;
                        foreach( $titles as $title )
                            if( $title == $item['title'] )
                                $dupe = true;

                        if( !$dupe )
                        {
                            $count++;
                            if( $count == 6 )
                            {
                                $extended = true;
                                echo "<li id=\"show_more_feeds_$column\"><a href=\"javascript:void(o)\" onclick=\"showFeeds($column)\">more...</a></li><li class=\"morefeeds\" ><div id=\"more_feeds_$column\" class=\"hidden\"><ul>";
                            }

                            $titles[] = $item['title'];
                            echo "<li><a title=\"{$item['source']}\" href=\"{$item['link']}\">{$item['title']}</a></li>";
                        }
                    }
                }

                unset($titles);

                if( $extended )
                    echo '</ul></div></li>';

                echo '</ul></td>';
            }
            echo '</tr></table>';
        }
    ?>
    </div>
    <div class="cleared"></div>

    <?php
    if (!isset($site_js_loaded) || !$site_js_loaded) {
        echo "<script type=\"text/javascript\" src=\"{$GLOBALS['cdnPath']}/js/site.js?v=" . VER_JS . "\"></script>\n";
        $hasJquery = true;
    }
    if (!array_key_exists('HTTP_CACHE_CONTROL', $_SERVER) &&    // skip manual browser refreshes
        is_file('./js/experiment.js')) {
        $headers = $_SERVER;
        preg_match_all('%(?P<browser>Camino|Kindle(\ Fire\ Build)?|Firefox|Safari|MSIE|Chrome|IEMobile|Opera|Silk|Lynx|Version|Wget|curl|NintendoBrowser|PLAYSTATION|AppleWebKit\ \d+)(?:;?)(?:(?:[/ ])(?P<version>[0-9]+)|/(?:[A-Z]*))%x',
                        $_SERVER['HTTP_USER_AGENT'], $result, PREG_PATTERN_ORDER);
        $browser = "{$result['browser'][0]} {$result['version'][0]}";
        echo "<script>\n";
        echo "wptJSVer = '" . VER_JS . "';\n";
        echo "wptBrowser = '$browser';\n";
        include ('./js/experiment.js');
        echo "</script>\n";
        //echo "<script type=\"text/javascript\" src=\"{$GLOBALS['cdnPath']}/js/experiment.js?v=" . VER_JS . "\"></script>\n";
    }

    ?>
    <script type="text/javascript">
        function showFeeds(column)
        {
            var label = document.getElementById("show_more_feeds_" + column);
            label.parentNode.removeChild( label );

            document.getElementById("more_feeds_" + column).className = "";
            return false;
        }
    </script>
    <?php
    if (file_exists('./settings/server/customfooter.inc.php')) {
        include('./settings/server/customfooter.inc.php');
    } elseif (file_exists('./settings/common/customfooter.inc.php')) {
        include('./settings/common/customfooter.inc.php');
    } elseif (file_exists('./settings/customfooter.inc.php')) {
        include('./settings/customfooter.inc.php');
    }
    ?>
    <?php
    if(!isset($noanalytics) && extension_loaded('newrelic'))
        echo @newrelic_get_browser_timing_footer();
    ?>

    <div id="experiment-timing" style="color: #77A;"></div>
