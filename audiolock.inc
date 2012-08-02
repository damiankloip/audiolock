<?php

/**
 * @file
 * Drupal Audiolock API classes.
 */

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
        $message = t('Audiolock API error -- Error code: @error_code - @error. called by @caller',
          array('@error_code' => $response->error_code, '@error' => $response->error, '@caller' => $method));

        drupal_set_message($message, 'error');
        watchdog('audiolock', $message);
      }
      // We have no errors, and a valid response.
      elseif (!empty($response->response)) {
        $unserialized = unserialize($response->response);
        // if we unserialize a normal string, we will get an empty return value.
        return $unserialized ? $unserialized : $response->response;
      }
    }
    catch (SoapFault $sf) {
      watchdog('audiolock', $sf->getMessage());
    }

    return FALSE;
  }

  /**
   * Adds a recipient (user) to an Audiolock account.
   *
   * @param $params Array:
   *   - email (required), the recipients email address
   *   - name (optional), the recipients name
   *   - address (optional), the recipients postal address
   *   - postcode (optional), the recipients postcode or zip
   *   -  group (optional), id of an existing group, see createGroup.
   *   - fail_on_dup (optional), boolen, default is false, if set to true it
   *     will fail if recipient already exists in your account otherwise it will return
   *     the existing recipient id as the response.
   */
  public function addRecipient(array $params = array()) {
    return $this->request('addRecipient', $params);
  }

  /**
   * Gets all recipients for an Audiolock account.
   *
   * @param $params Array:
   *   - match (optional), a string to match against, e.g. “Richard”
   *   - track (optional), the unique identifier for the track they have been sent, see addTrack
   *   - offset (optional), the start position of the returned results
   *   - limit (optional), the maximum number of results returned
   *   - sort (optional), what field to sort by (contact_name, contact_email)
   *   - direction (optional), sort direction (asc, desc)
   *   - group (optional), the id of an existing group, see createGroup
   */
  public function getRecipients() {
    return $this->request('getRecipients');
  }

  /**
   * Gets a single recipient from an Audiolock account.
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
   * Edits a single recipient.
   *
   * @param $params
   *   @see addRecipient for parameters.
   */
  public function editRecipient(array $params = array()) {
    return $this->request('editRecipient', $params);
  }

  /**
   * Edits a single recipient.
   *
   * @param $params
   *   - recipient_id (required), id or array of ids of existing recipients.
   *     TODO: Change param to be recipient_id(s).
   */
  public function deleteRecipients(array $params = array()) {
    return $this->request('deleteRecipient', $params);
  }

  /**
   * Adds/uploads a track to an Audiolock account.
   *
   * @param $params Array:
   *   - artist (required)
   *   - track_name (required), your reference to the track
   *   - mix_name (optional), the specific mix of the track
   *   - track_file_name (required), the file name of the track, e.g. ‘PVD – 45rpm.mp3’
   *   - track_file_contents (required), publically accessible URL of the source file,
   *     this is downloaded immediately and should be deleted once addTrack returns the
   *     UID of the newly added track / success.
   *   - artwork_file_contents (optional), base64 encode of the artwork file’s contents
   *   - isrc (optional), International Standard Recording Code for the track,
   *     with or without the dashes
   *   - release_date (optional), timestamp of the track’s release date
   *   - encode (optional), boolean, default is true, if set to false when this track is
   *     delivered it will not be watermarked.
   */
  public function addTrack(array $params = array()) {
    return $this->request('addTrack', $params);
  }

  /**
   * Gets info on a single track.
   *
   * @param $track_uid (int)
   *   The unique Audiolock track ID.
   */
  public function getTrack($track_id) {
    return $this->request('getTrack', array('track_id' => $track_id));
  }

  /**
   * Gets info track info.
   *
   * @param $params array
   *   - offset (optional), the track record to start at
   *   - limit (optional), the maximum number of tracks to return
   *   - sort (optional), what field to sort by (artist, track_name, length, date_added)
   *   - direction (optional), sort direction (asc, desc)
   */
  public function getTracks(array $params = array()) {
    return $this->request('getTracks', $params);
  }

  /**
   * Edits info on a single track.
   *
   * @param $params
   *   @see addTrack() method for parameters.
   *   Probably modifying return value from getTrack would be sensible.
   */
  public function editTrack(array $params = array()) {
    return $this->request('editTrack', $params);
  }

  /**
   * Deletes one or more tracks from an Audiolock account.
   *
   * @param $params String/array:
   *   - tracks (required), unique indentifier or array of unique indentifiers
   *   @see see addTrack
   */
  public function deleteTracks(array $params = array()) {
    return $this->request('deleteTracks', $params);
  }

  /**
   * Adds an album to an Audiolock account.
   *
   * @param $params array
   *   - name (required), the title of the album
   *   - artist (optional), the artist of the album, e.g. “Various Artists”
   *     or “Paul van Dyk”
   *   - catalog_number (optional), the catalog number of the album, e.g. VAN1234D
   *   - tracks (optional), the unique identifier or array of unique identifiers
   *     of the tracks you wish to send, see addTrack
   *   - artwork_file_name (optional), the file name of the artwork, ‘e.g. picture001.jpg’
   *   - artwork_file_contents (optional), base64 encode of the artwork file’s contents
   *   - release_date (optional), timestamp of the album’s release date
   */
  public function addAlbum(array $params = array()) {
    return $this->request('addAlbum', $params);
  }

  /**
   * Deletes one or more albums from an Audiolock account.
   *
   * @param $params String/array:
   *   - albums (required), unique indentifier or array of unique indentifiers
   *   @see see addAlbum
   */
  public function deleteAlbums($ids) {
    return $this->request('deleteAlbums', array('albums' => $ids));
  }

  /**
   * Gets info on a single album.
   *
   * @param $album_id (int)
   *   The unique Audiolock album ID.
   */
  public function getAlbum($album_id) {
    return $this->request('getAlbum', array('album_id' => $album_id));
  }

  /**
   * Gets album info.
   *
   * @param $params array
   *   - offset (optional), the track record to start at
   *   - limit (optional), the maximum number of tracks to return
   *   - sort (optional), what field to sort by (artist, track_name, length, date_added)
   *   - direction (optional), sort direction (asc, desc)
   */
  public function getAlbums(array $params = array()) {
    return $this->request('getAlbums', $params);
  }

  /**
   * Edits a single album.
   *
   * @param $params
   *   @see addAlbum for parameters.
   */
  public function editAlbum(array $params = array()) {
    return $this->request('editAlbum', $params);
  }

  /**
   * Generates a download link to a track.
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

  /**
   * Generates a downloadable zip archive of tracks.
   *
   * @param $params array
   *   - tracks (required), array of unique identifiers of tracks, see addTrack
   *   - format (required), the id of the format required (see footer notes)
   *   - recipient_id (required), the of an existing recipients
   *     @see addRecipient, alternatively a two part array containing name +
   *     email of the recipient e.g. array(‘John Doe’, ‘john.doe@google.com’).
   *     This contact will subsequently be added to your account.
   *   - expires (optional), float, 7 – 30, default 7, the number of days after
   *     generating that the link expires
   *   - zip_name (optional), the name of the zip file when downloaded
   */
  public function generateZipDownloadLink(array $params = array()) {
    return $this->request('generateZipDownloadLink', $params);
  }

} // DrupalAudiolock.
