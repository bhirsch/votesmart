See VoteSmart module README.txt for roadmap....

2. SWS SalesForce module. 
- Provide a web form for accepting params which will be sent to VoteSmart
  module to request data. 
- Process VoteSmart data by flattening it out and storing it in a single table,
  neatly formatted for sending to SalesForce. 


OPPONENT: 

Road Map: 
Create four fields: "Opponent Primary" and "Opponent General"
                    "Election Day Primary" and "Election Day General"


SELECT CONCAT(State, ' - ', District, ', ', Office) AS district,
COUNT(district) AS count FROM  sf_votesmart_to_salesforce GROUP BY district
ORDER BY count DESC;



Notes from data testing below.
Sample size: 2512 candidates from 7 states (RI, WI, IA, KS, MO, MI, KY)

WEBSITES
RESULTS:
827 websites in votesmart among 773 candidates
773 websites in salesforce
53 website2 in salesforce

SELECT candidateId, webAddress FROM votesmart_address_webaddress WHERE
LENGTH(webAddress) > 2 AND webAddressType = 'Website';

SELECT VoteSmartID, Website FROM sf_votesmart_to_salesforce WHERE
LENGTH(Website) > 2 ;

SELECT VoteSmartID, Website2 FROM sf_votesmart_to_salesforce WHERE
LENGTH(Website2) > 2 ;


SELECT DISTINCT c.candidateId FROM votesmart_candidate c JOIN
votesmart_address_webaddress w ON  c.candidateId = w.candidateId WHERE
LENGTH(webAddress) > 2 AND webAddressType = 'Website';




EMAIL
RESULTS: 
797 emails in votesmart among 737 candidates
737 emails in salesforce

FUP: Create an email2 field? 

SELECT candidateId, webAddress FROM votesmart_address_webaddress WHERE
LENGTH(webAddress) > 2 AND webAddressType = 'Email';

SELECT VoteSmartID, Email FROM sf_votesmart_to_salesforce WHERE LENGTH(Email)
> 2 ;

SELECT DISTINCT c.candidateId FROM votesmart_candidate c JOIN
votesmart_address_webaddress w ON  c.candidateId = w.candidateId WHERE
LENGTH(webAddress) > 2 AND webAddressType = 'Email';




CELL PHONES
RESULTS:
121 cell phones in votesmart among 117 candidates (including 2 emails
masquerading as cell numbers)
117 cell phones in sf (2 emails snuck in here. we're not cleaning votesmart
data before it comes in)

SELECT candidateId, webAddress FROM votesmart_address_webaddress WHERE
LENGTH(webAddress) > 2 AND webAddressType = 'Cell Phone';

SELECT VoteSmartID, PhoneCell FROM sf_votesmart_to_salesforce WHERE
LENGTH(PhoneCell) > 2 ;

SELECT DISTINCT c.candidateId FROM votesmart_candidate c JOIN
votesmart_address_webaddress w ON  c.candidateId = w.candidateId WHERE
LENGTH(webAddress) > 2 AND webAddressType = 'Cell Phone';



WEBMAIL
RESULTS: 
276 webmails in votesmart among 264 candidates
264 webmails in salesforce


SELECT candidateId, webAddress FROM votesmart_address_webaddress WHERE
LENGTH(webAddress) > 2 AND webAddressType = 'Webmail';

SELECT VoteSmartID, Webmail FROM sf_votesmart_to_salesforce WHERE
LENGTH(Webmail) > 2 ;

SELECT DISTINCT c.candidateId FROM votesmart_candidate c JOIN
votesmart_address_webaddress w ON  c.candidateId = w.candidateId WHERE
LENGTH(webAddress) > 2 AND webAddressType = 'Webmail';
