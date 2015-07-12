<?php

// Include twitteroauth
require "twitteroauth/autoload.php";
use Abraham\TwitterOAuth\TwitterOAuth;

// Set keys
$consumerKey = 'Fbk35xT0WLc6xnZ7sfBaW5LOw';
$consumerSecret = 'EqK34wLITUzdI8C4Xz0FHPUXKdZl71wdhU2dDjFvKsxutO7dXU';
$accessToken = '3276318697-7pZiNWfVXSN2G1BHQB4bJIGhScjsNto8SCohouY';
$accessTokenSecret = 'QLJpsHwfnjQnDzAtGbWQegj2jDeP9baoqHWnil9lWvHjo';

date_default_timezone_set('America/Detroit');
$date = date('m/d/Y h:i:s a', time());

// Create object
$tweet = new TwitterOAuth($consumerKey, $consumerSecret, $accessToken, $accessTokenSecret);

// Set status message
$tweetMessage = 'Temp1 = '.$_GET["temp1"].' Photo1 = '.$_GET["photo1"].' @ '. $date;

// Check for 140 characters
if(strlen($tweetMessage) <= 140)
{
    // Post the status message
    $tweet->post('statuses/update', array('status' => $tweetMessage));
}

?>