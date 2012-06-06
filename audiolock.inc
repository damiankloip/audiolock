<?php

/**
 * SoapClient wrapper class.
 * Make requests to the Audiolock API using this.
 *
 * wsdl: 'http://www.audiolock.net/soapServerv2.php?wsdl'
 * original api key: 'db158f7c02f60e89cbb41b73e563d85c-e12202ed252b58eefd5b34afcaaf1d2a'
 */
class DrupalAudiolock {

  // Audiolock API key.
  protected $api_key;

  // Audiolock wsdl URL.
  protected $wsdl;

  // SoapClient storage.
  protected $client;

  /**
   * Constructor.
   */
  public function __construct() {
    $this->api_key = trim(variable_get('audiolock_api_key', ''));
    $this->wsdl = trim(variable_get('audiolock_wsdl', 'http://www.audiolock.net/soapServerv2.php?wsdl'));

    // Instantiate our SoapClient class and store it.
    $this->client = new SoapClient($this->wsdl);
  }

  /**
   * Request method for all calls to Audiolock API.
   */
  protected function request($method, array $params = array()) {
    // Add the api_key parameter to requests.
    $params += array('api_key' => $this->api_key);

    try {
      $response = $this->client->{$method}($params);
      // If we have any errors.
      if (!empty($response->error_code)) {
        $message = t('Audiolock API error -- Error code: @error_code - @error.',
          array('@error_code' => $response->error_code, '@error' => $response->error));

        drupal_set_message($message, 'error');
        watchdog('audiolock', $message);
      }
      // We have no errors, and a valid response.
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
   * Add a recipient (user) to an Audiolock account.
   *
   * @param $params Array:
   * - email (required), the recipients email address
   * - name (optional), the recipients name
   * - address (optional), the recipients postal address
   * - postcode (optional), the recipients postcode or zip
   * -  group (optional), id of an existing group, see createGroup.
   * - fail_on_dup (optional), boolen, default is false, if set to true it will fail if recipient already exists
   *   in your account otherwise it will return the existing recipient id as the response.
   */
  public function addRecipient(array $params = array()) {
    return $this->request('addRecipient', $params);
  }

  /**
   * Get all recipients for an Audiolock account.
   *
   * @param $params Array:
   * - match (optional), a string to match against, e.g. “Richard”
   * - track (optional), the unique identifier for the track they have been sent, see addTrack
   * - offset (optional), the start position of the returned results
   * - limit (optional), the maximum number of results returned
   * - sort (optional), what field to sort by (contact_name, contact_email)
   * - direction (optional), sort direction (asc, desc)
   * - group (optional), the id of an existing group, see createGroup
   */
  public function getRecipients() {
    return $this->request('getRecipients');
  }

  /**
   * Get a single recipient from an Audiolock account.
   *
   * @param $recipient_id:
   *   The numeric Audiolock recipient id.
   * 
   * @return
   *   Recipient info object.
   */
  public function getRecipient($recipient_id) {
    return $this->request('getRecipients', array('recipient_id' => $recipient_id));
  }

  /**
   * Edit a single recipient.
   *
   * @param $params
   *   See addRecipient for parameters.
   */
  public function editRecipient(array $params = array()) {
    return $this->request('editRecipient', $params);
  }

  /**
   * Edit a single recipient.
   *
   * @param $params
   *   - recipient_id (required), id or array of ids of existing recipients.
   *     TODO: Change param to be recipient_id(s).
   */
  public function deleteRecipients(array $params = array()) {
    return $this->request('deleteRecipient', $params);
  }

  /**
   * Add/upload a track to an Audiolock account.
   *
   * @param $params Array:
   * - artist (required)
   * - track_name (required), your reference to the track
   * - mix_name (optional), the specific mix of the track
   * - track_file_name (required), the file name of the track, e.g. ‘PVD – 45rpm.mp3’
   * - track_file_contents (required), publically accessible URL of the source file, this is downloaded
   *   immediately and should be deleted once addTrack returns the UID of the newly added track /
   *   success.
   * - artwork_file_contents (optional), base64 encode of the artwork file’s contents
   * - isrc (optional), International Standard Recording Code for the track, with or without the dashes
   * - release_date (optional), timestamp of the track’s release date
   * - encode (optional), boolean, default is true, if set to false when this track is delivered it will not
   *   be watermarked.
   */
  public function addTrack(array $params = array()) {
    return $this->request('addTrack', $params);
  }

  /**
   * Get info on a single track.
   *
   * @param $track_uid (int)
   *   The unique Audiolock track ID.
   */
  public function getTrack($track_uid) {
    return $this->request('getTrack', array('track_id' => $track_id));
  }

  /**
   * Edit info on a single track.
   *
   * @param $params
   *   See addTrack() method for parameters.
   *   Probably modifying return value from getTrack would be sensible.
   */
  public function editTrack(array $params = array()) {
    return $this->request('editTrack', $params);
  }

  /**
   * Delete one or more tracks from an AUdiolock account.
   *
   * @param $params String/array:
   * - tracks (required), unique indentifier or array of unique indentifiers, see addTrack
   */
  public function deleteTracks(array $params = array()) {
    return $this->request('deleteTracks', $params);
  }

  /**
   * Generate a download link to a track.
   *
   * @param $params Array:
   * - track (required), the unique identifier for the track, see addTrack
   * - format (required), the id of the format required
   * - recipient_id (required), the of an existing recipients, see addRecipient, alternatively a two part
   *   array containing name + email of the recipient e.g. array(‘John Doe’, ‘john.doe@google.com’).
   *   This contact will subsequently be added to your account
   * - expires (optional), float, 7 – 30, default 7, the number of days after generating that the link
   *   expires.
   */
  public function generateDownloadLink(array $params = array()) {
    return $this->request('generateDownloadLink', $params);
  }

} // DrupalAudiolock.
