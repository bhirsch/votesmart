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



NOTE:
change $key in lib/slipphp/config.php
