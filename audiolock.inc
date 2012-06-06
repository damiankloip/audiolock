<?php

/**
 * SoapClient wrapper class.
 * Make requests to the Audiolock API using this.
 *
 * wsdl: 'http://www.audiolock.net/soapServerv2.php?wsdl'
 * original api key: 'db158f7c02f60e89cbb41b73e563d85c-e12202ed252b58eefd5b34afcaaf1d2a'
 */
class DrupalAudiolock {

  // Audolock API key.
  protected $api_key = trim(variable_get('audiolock_api_key', ''));

  // Audolock wsdl URL.
  protected $wsdl = trim(variable_get('audiolock_wsdl', 'http://www.audiolock.net/soapServerv2.php?wsdl'));

  // SoapClient storage.
  protected $client;

  public function __construct() {
    // Instantiate our SoapClient class.
    $this->client = new SoapClient($this->wsdl);
  }

  /**
   * Request method for all calls to Audiolock API.
   */
  protected function request($method, $params) {
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
