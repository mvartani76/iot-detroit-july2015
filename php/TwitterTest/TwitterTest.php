<?php

// Include twitteroauth
require "twitteroauth/autoload.php";
use Abraham\TwitterOAuth\TwitterOAuth;

// Set keys
$consumerKey = 'YOUR-CONSUMER-KEY';
$consumerSecret = 'YOUR-CONSUMER-SECRET';
$accessToken = 'YOUR-ACCESS-TOKEN';
$accessTokenSecret = 'YOUR-ACCESS-TOKEN-SECRET';

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