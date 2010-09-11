NOTES FOR FUTURE REWRITE: 
Making this whole thing "list oriented" was a mistake. This was originally
created in order to use VoteSmart data to do build lists of candidates to be
imported into SalesForce. But it's really doing three separate things, that should really be packaged into three separate modules:

1. VoteSmart modules.
- votesmart.module accept $class, $method, $args, and return $xml 
  (maybe in the future bake in some other end-user stuff for interactong w/ API)
- vsdata.module:   
-- accept requests for data (parameters like "MA" and "2010")
-- process requests and store data inside votesmart_* tables 
   (which are caching the XML data sent from VoteSmart).
-- provide a hook that notifies other modules if their requests have been
   processed and fulfilled.

2. SWS SalesForce module. 
- Provide a web form for accepting params which will be sent to VoteSmart
  module to request data. 
- Process VoteSmart data by flattening it out and storing it in a single table,
  neatly formatted for sending to SalesForce. 
- Provide a list of links to views which use args as params for lists it has
  built. e.g. salesforce/ma/2010/csv, salesforce/ia/2010/csv, etc.

3. List Building (other modules do this better...)
	Expose swssf table with TW
	Make data into an Exportable view with views_bonus
 


Get typeId here:
http://api.votesmart.org/Office.getTypes?key=8be7942478e869e453aa7a5b48de02eb

Then get officeId here:
(e.g. L for state legislatures)
http://api.votesmart.org/Office.getOfficesByType?typeId=L&key=8be7942478e869e453aa7a5b48de02eb



Then get candidates state-by-state like this:

State Senate (officeId=9
MA 
http://api.votesmart.org/Candidates.getByOfficeState?officeId=9&stateId=MA&key=8be7942478e869e453aa7a5b48de02eb

House of Reps (officeId=8)
MA
http://api.votesmart.org/Candidates.getByOfficeState?officeId=8&stateId=MA&key=8be7942478e869e453aa7a5b48de02eb

State Assembly (officeId=7)
CA
http://api.votesmart.org/Candidates.getByOfficeState?officeId=7&stateId=CA&key=8be7942478e869e453aa7a5b48de02eb


Get candididates' basic contact info like this:
http://api.votesmart.org/Address.getOfficeByOfficeState?officeId=9&stateId=MA&key=8be7942478e869e453aa7a5b48de02eb
(note this does not give you candidateIds for each candidate)

( OR 
Get each candidate's basic contact info like this:
http://api.votesmart.org/Address.getCampaign?candidateId=81542&key=8be7942478e869e453aa7a5b48de02eb
)

Get each candidate's website and email info like this:
http://api.votesmart.org/Address.getCampaignWebAddress?candidateId=81542&key=8be7942478e869e453aa7a5b48de02eb



NOTES: 
If you use VoteSmart library, change $key in lib/slipphp/config.php


VOTESMART DATA NOTES:

votesmart_candidate
------------------------------------------------
electionStatus field doesn't have 'won', it includes:
| Running           |
| Lost              |
| Too Close To Call | 

