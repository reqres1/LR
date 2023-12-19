DeleteABooking()
{
	int i;
	int flightIDCount;
	int cgiFieldsCount;
	char requestBody[4096];
	char cgifields[4096];
	char tempBuffer[256];
	
	lr_start_transaction("UC02_DeleteABooking");
	
	lr_start_transaction("MainWelcomePage");
	
	web_add_auto_header("Sec-Fetch-Dest", 
		"document");

	web_add_auto_header("Sec-Fetch-Site", 
		"none");

	web_add_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_reg_save_param_regexp(
		"ParamName=userSession",
		"RegExp=userSession\" value=\"(.*?)\"/>",
		SEARCH_FILTERS,
		"Scope=BODY",
		LAST);
	
	web_reg_find("Text=A Session ID has been created", LAST);
	
	web_url("welcome.pl", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?signOff=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/WebTours/", 
		"Snapshot=t230.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("MainWelcomePage",LR_AUTO);
	
	lr_think_time(2);

	lr_start_transaction("LogIn");
	
	web_revert_auto_header("Sec-Fetch-Dest");

	web_revert_auto_header("Sec-Fetch-Site");
	
	web_add_header("Origin", 
		"{protocol}://{host}:{port}");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	web_add_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_reg_find("Text=User password was correct",LAST);
	
	web_submit_data("login.pl", 
		"Action={protocol}://{host}:{port}/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?in=home", 
		"Snapshot=t241.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=userSession", "Value={userSession}", ENDITEM, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=login.x", "Value=0", ENDITEM, 
		"Name=login.y", "Value=0", ENDITEM, 
		"Name=JSFormSubmit", "Value=off", ENDITEM, 
		LAST);

	lr_end_transaction("LogIn",LR_AUTO);

	lr_think_time(2);

	lr_start_transaction("ClickItinerary");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	web_add_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_header("Upgrade-Insecure-Requests", 
		"1");

	web_reg_save_param(
		"FlightIDParam",
	    "LB=<input type=\"hidden\" name=\"flightID\" value=\"", 
	    "RB=\"",
	    "Ord=ALL",
	    "Search=Body", 
	    LAST);
	
	web_reg_save_param(
    	"CgiFieldsParam",
    	"LB=<input type=\"hidden\" name=\".cgifields\" value=\"",
    	"RB=\"",
    	"Ord=ALL",
    	"Search=Body",
    	LAST);
	
	web_reg_find("Text=A total of",LAST);
	
	web_url("welcome.pl_2", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?page=itinerary", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t133.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("ClickItinerary",LR_AUTO);

	lr_think_time(2);

	lr_start_transaction("CanselReservation");

	web_add_header("Origin", 
		"{protocol}://{host}:{port}");

	web_add_auto_header("Sec-Fetch-Dest", 
		"frame");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_auto_header("Sec-Fetch-Site", 
		"same-origin");

	web_add_auto_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	web_reg_find("Text=A total of",LAST);
	
	flightIDCount = atoi(lr_eval_string("{FlightIDParam_count}"));
	cgiFieldsCount = atoi(lr_eval_string("{CgiFieldsParam_count}"));
	
	strcpy(requestBody, "");

	for (i = 1; i <= flightIDCount; i++) {
    char flightIDValue[256];
    snprintf(flightIDValue, sizeof(flightIDValue), "%s", lr_eval_string(lr_paramarr_idx("FlightIDParam", i)));
    sprintf(tempBuffer, "&flightID=%s", flightIDValue);
    strcat(requestBody, tempBuffer);
	}
	
	lr_save_string(requestBody, "requestBody");
	
	strcpy(cgifields, "");

    for (i = 1; i <= cgiFieldsCount; i++) {
    char cgiFieldValue[256];
    snprintf(cgiFieldValue, sizeof(cgiFieldValue), "%s", lr_eval_string(lr_paramarr_idx("CgiFieldsParam", i)));
    sprintf(tempBuffer, "&.cgifields=%s", cgiFieldValue);
    strcat(cgifields, tempBuffer);
	}
	
	lr_save_string(cgifields, "cgifields");
	
    web_custom_request("itinerary.pl",
    	"Method=POST",
    	"URL={protocol}://{host}:{port}/cgi-bin/itinerary.pl",
    	"Resource=0",
    	"EncType=application/x-www-form-urlencoded",
    	"Referer={protocol}://{host}:{port}/cgi-bin/itinerary.pl",
    	"Snapshot=t6.inf",
    	"Mode={protocol}",
    	"Body=1=on{requestBody}&removeFlights.x=64&removeFlights.y=9&{cgifields}",
    	LAST);

	lr_end_transaction("CanselReservation",LR_AUTO);
	
	lr_think_time(2);

	lr_start_transaction("SignOff");

	web_revert_auto_header("Sec-Fetch-User");

	web_reg_find("Text=Welcome to the Web Tours site",LAST);
	
	web_url("welcome.pl_2", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?page=menu&in=itinerary", 
		"Snapshot=t315.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("SignOff",LR_AUTO);

	lr_end_transaction("UC02_DeleteABooking",LR_AUTO);
	
	return 0;
}