<?php
/**
 * @file
 *  votesmart_candidate_contact_info.inc
 */

/**
 * @param $state
 *  string, state code
 * 
 * @param $year
 *  integer, year of election season
 */
function votesmart_candidate_contact_info($state, $year = null) {
//dsm($state);
//dsm($year);
 
  // Get all ids for the offices we want to look up.
  $office_ids = votesmart_get_office_ids();
  //dsm($office_ids);

  // Get all candidates running for each elected office.
  // $candidate_ids = votesmart_get_candidate_ids();
  foreach ($office_ids as $office_id) {
    $class = 'Candidates';
    $method = 'getByOfficeState';
    $key = '8be7942478e869e453aa7a5b48de02eb';
    $args = array('officeId' => $office_id, 'stateId' => strtoupper($state));
    $xml = votesmart_xml($class, $method, $key, $args);

    $candidate_ids = array();
    foreach ($xml->candidate as $candidate) {
      $id = $candidate->candidateId;
      $id = (string)$id; // convert simplexml object to string
      $candidate_ids[] = $id;
// TODO store these in a table, queued for processing.
    }
    //dsm($candidate_ids);
   
    $delay = 0; 
    // Iterate through candidates, getting contact info for each
// TODO pull from db, process one after the other
    foreach ($candidate_ids as $candidate_id) {
      // Try 100 times, then give up
      $attempt = 0;
// CONTINUE HERE

//dsm($candidate_id);
      // get basic contact info
      $class = 'Address';
      $method = 'getCampaign';
      $key = '8be7942478e869e453aa7a5b48de02eb';
      $args = array('candidateId' => $candidate_id);
      $xml = votesmart_xml($class, $method, $key, $args);
// TODO update db table

/*
      $candidate_ids = array();
      foreach ($xml->candidate as $candidate) {
        $id = $candidate->candidateId;
        $id = (string)$id; // convert simplexml object to string
        $candidate_ids[] = $id;
      }

      // get website/email info
// */
    }

  }

  // make sure directory exists 
  $directory = file_directory_path() ."/votesmart/"; 
  file_check_directory($directory, FILE_CREATE_DIRECTORY);

  // save results to a file
  $file_name = $state .'-'. $year .'.csv';
  $file_path = "$directory/$file_name"; 
  file_put_contents($file_path, 'this is a test');

  // provide user a link to the file
  global $base_url;
  $path = $base_url .'/'. $file_path; 
  $link = l($file_name, $path);
  
  return $link;
}

