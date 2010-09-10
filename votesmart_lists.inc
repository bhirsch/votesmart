<?php 
/**
 * @file
 *  votesmart_lists.inc
 */

/**
 * Page callback for votesmart/lists.
 */
function votesmart_lists() {
  $results = db_query("SELECT file_name, status, candidate_records, address_records, phone_records, webaddress_records, timestamp "
                     ." FROM {votesmart_list} "); 
  while ($row = db_fetch_array($results)) {
    if ($row['status'] == 'complete') {
      // TODO Make file_name link to .csv file in files/votesmart directory.
    }
    $rows[] = $row;
  }
  $header = array('file_name', 'status', 'candidate_records', 'address_records', 'phone_records', 'webaddress_records', 'timestamp');
  $caption = t('To build a list go to votesmart/buildlist/[state]/[year]');
  $output = theme('table', $header, $rows);

  return $output;
}