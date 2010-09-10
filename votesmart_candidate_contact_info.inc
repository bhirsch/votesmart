<?php
/**
 * @file
 *  votesmart_candidate_contact_info.inc
 */

/**
 * Page callback for votesmart/%/%
 * 
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

  // Get all candidates running for each elected office
  // and store data in local votesmart_candidate table. 
  $i = 0; 
  foreach ($office_ids as $name => $office_id) {
    // todo function should return something here for testing/error handling. 
    $count = votesmart_get_candidates($office_id, $state, $year); 
    if ($count) {
      // Create a record in votesmart_list table 
      // to indicate this list is being processed (on cron).   
      // TODO $state_$year_$name
      $file_name = $state .'_'. $year .'_'. $name; 
      $timestamp = time();
      db_query("INSERT INTO {votesmart_list} "
              ."(file_name, status, candidate_records, timestamp) "
              ."VALUES ('%s', '%s', %d, %d) ", 
               $file_name,
               'pending',  
               $count, 
               $timestamp );
    $i++;
    }
  } 

  if ($i) { 
    $link = l('votesmart/lists', 'votesmart/lists');  
    return "Thanks. $state $year candidates  have been added to the queue for processing. Run cron to process the list(s). Visit $link to check the list's status."; 
  } else {
    $state = strtoupper($state);
    return "Sorry. VoteSmart didn't return any records for $state in $year.";
  }

}

/**
 * Store VoteSmart candidate info in votesmart_candidate table.
 * 
 * @param $office_id
 *  string, votesmart officeId
 * 
 * @param $state
 *  string, two digit state code
 * 
 * @param $year
 *  integer, optional, defaults to current year
 * 
 * @return
 *  todo, error handling, return success/failure or something like that.
 */ 
function votesmart_get_candidates($office_id, $state, $year = null) {
  $class = 'Candidates';
  $method = 'getByOfficeState';
  $key = '8be7942478e869e453aa7a5b48de02eb';
  $args = array('officeId' => $office_id, 'stateId' => strtoupper($state));
  $xml = votesmart_xml($class, $method, $key, $args);

  $count = 0;
  $candidate_ids = array();
  foreach ($xml->candidate as $candidate) {
    // count records
    $count++; 

    $candidateId = (string)$candidate->candidateId;
    $firstName =  (string)$candidate->firstName;
    $nickName =  (string)$candidate->nickName;
    $middleName =  (string)$candidate->middleName;
    $preferredName =  (string)$candidate->preferredName;
    $lastName =  (string)$candidate->lastName;
    $suffix =  (string)$candidate->suffix;
    $title =  (string)$candidate->title;
    $ballotname =  (string)$candidate->ballotname;
    $electionParties =  (string)$candidate->electionParties;
    $electionStatus =  (string)$candidate->electionStatus;
    $electionStage =  (string)$candidate->electionStage;
    $electionDistrictId =  (string)$candidate->electionDistrictId;
    $electionDistrictName =  (string)$candidate->electionDistrictName;
    $electionOffice =  (string)$candidate->electionOffice;
    $electionOfficeId = (string)$candidate->electionOfficeId;
    $electionStateId =  (string)$candidate->electionStateId;
    $electionOfficeTypeId =  (string)$candidate->electionOfficeTypeId;
    $electionYear =  (string)$candidate->electionYear;
    $electionSpecial =  (string)$candidate->electionSpecial;
    $electionDate =  (string)$candidate->electionDate;
    $officeParties =  (string)$candidate->officeParties;
    $officeDistrictId =  (string)$candidate->officeDistrictId;
    $officeDistrictName =  (string)$candidate->officeDistrictName;
    $officeStateId =  (string)$candidate->officeStateId;
    $officeId =  (string)$candidate->officeId;
    $officeName =  (string)$candidate->officeName;
    $officeTypeId =   (string)$candidate->officeTypeId;

    // Check if record for this candidate already exists.
    if (db_result(db_query("SELECT candidateId FROM {votesmart_candidate} WHERE candidateId = %d", $candidateId))) {
      // If update candidate's record with newest information. 
      // todo Add timestamp. 
      db_query("UPDATE {votesmart_candidate} "
              ."SET 
      firstName = '%s', 
      nickName = '%s',
      middleName = '%s',
      preferredName = '%s',
      lastName = '%s',
      suffix =  '%s',
      title =  '%s',
      ballotname = '%s',
      electionParties ='%s',
      electionStatus = '%s',
      electionStage =  '%s',
      electionDistrictId = '%s',
      electionDistrictName = '%s',
      electionOffice = '%s',
      electionOfficeId ='%s',
      electionStateId =  '%s',
      electionOfficeTypeId = '%s',
      electionYear = '%s',
      electionSpecial = '%s',
      electionDate = '%s',
      officeParties = '%s',
      officeDistrictId = '%s',
      officeDistrictName = '%s',
      officeStateId = '%s',
      officeId ='%s',
      officeName = '%s',
      officeTypeId = '%s' 
      WHERE candidateId = %d ", 
      $firstName, 
      $nickName, 
      $middleName,  
      $preferredName, 
      $lastName, 
      $suffix, 
      $title,  
      $ballotname, 
      $electionParties, 
      $electionStatus, 
      $electionStage,  
      $electionDistrictId, 
      $electionDistrictName, 
      $electionOffice, 
      $electionOfficeId, 
      $electionStateId,  
      $electionOfficeTypeId, 
      $electionYear, 
      $electionSpecial, 
      $electionDate, 
      $officeParties, 
      $officeDistrictId, 
      $officeDistrictName,  
      $officeStateId, 
      $officeId, 
      $officeName,  
      $officeTypeId,  
      $candidateId);
    } else { // Insert new record. 
      db_query("INSERT INTO {votesmart_candidate} "
            ."(candidateId, firstName, nickName, middleName, preferredName, lastName, suffix, title, ballotname, electionParties, electionStatus, electionStage, electionDistrictId, electionDistrictName, electionOffice, electionOfficeId, electionStateId, electionOfficeTypeId, electionYear, electionSpecial, electionDate, officeParties, officeDistrictId, officeDistrictName, officeStateId, officeId, officeName, officeTypeId ) " 
            ."VALUES (%d, '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s', '%s') ", 
            $candidateId, $firstName, $nickName, $middleName, $preferredName, $lastName, $suffix, $title, $ballotname, $electionParties, $electionStatus, $electionStage, $electionDistrictId, $electionDistrictName, $electionOffice, $electionOfficeId, $electionStateId, $electionOfficeTypeId, $electionYear, $electionSpecial, $electionDate, $officeParties, $officeDistrictId, $officeDistrictName, $officeStateId, $officeId, $officeName, $officeTypeId );
    }
  }
  return $count; 
}


