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
  protected $api_key;

  // Audolock wsdl URL.
  protected $wsdl;

  // SoapClient storage.
  protected $client;

  public function __construct() {
    $this->api_key = trim(variable_get('audiolock_api_key', ''));
    $this->wsdl = trim(variable_get('audiolock_wsdl', 'http://www.audiolock.net/soapServerv2.php?wsdl'));
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
      $response = $this->client->{$method}($params);
      if (!empty($response->error_code)) {
        $message = t('Audiolock API error -- Error code: @error_code - @error.', array('@error_code' => $response->error_code, '@error' => $response->error));
        drupal_set_message($message, 'error');
        watchdog('audiolock', $message);
      }
      elseif (!empty($response->response)) {
        return unserialize($response->response);
      }
    }
    catch (SoapFault $sf) {
      watchdog('audiolock', $sf->getMessage());
    }

    return FALSE;
  }

  /**
   * @todo.
   */
  public function addRecipient(array $params = array()) {
    return $this->request('addRecipient', $params);
  }

  /**
   * @todo.
   */
  public function getRecipients(array $params = array()) {
    return $this->request('getRecipients', $params);
  }

  /**
   * @todo.
   */
  public function addTrack(array $params = array()) {
    return $this->request('addTrack', $params);
  }

  /**
   * @todo.
   */
  public function generateDownloadLink(array $params = array()) {
    return $this->request('generateDownloadLink', $params);
  }

} // DrupalAudiolock.
