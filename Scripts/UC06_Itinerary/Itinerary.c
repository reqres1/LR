Itinerary()
{
	
	lr_start_transaction("UC06_Itinerary");
	
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
	
	lr_think_time(5);

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

	lr_think_time(5);

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

	lr_think_time(5);

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

	lr_end_transaction("UC06_Itinerary",LR_AUTO);
	
	return 0;
}