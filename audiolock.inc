<?php

/**
 * SoapClient wrapper class.
 * Make requests to the Audiolock API using this.
 */
class DrupalAudiolock {

  // Audolock API key.
  protected $api_key = 'NEED API KEY HERE';

  // Audolock wsdl URL.
  protected $wsdl = 'http://www.audiolock.net/soapServerv2.php?wsdl';

  // SoapClient storage.
  protected $client;

  public function __construct() {
    // Instantiate our SoapClient class.
    $this->client = new SoapClient($this->wsdl);
  }

  /**
   * Request method for all calls to Audiolock API.
   */
  public function request($method, $params) {
    // Add the api_key parameter to requests.
    $params += array('api_key' => $this->api_key);

    try {
      return $this->client->{$method}($params);
    }
    catch (SoapFault $sf) {
      watchdog('audiolock', $sf->getMessage());
      return FALSE;
    }
  }

} // DrupalAudiolock.