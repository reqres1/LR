LogIn()
{
	lr_start_transaction("MAIN_UC04_LogIn");

	lr_start_transaction("UC04_LogIn_01MainWelcomePage");

	web_add_header("Sec-Fetch-Dest", 
		"frame");

	web_add_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-Site", 
		"same-origin");

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
	
	lr_end_transaction("UC04_LogIn_01MainWelcomePage",LR_AUTO);
	
	lr_think_time(2);

	lr_start_transaction("UC04_LogIn_02LogIn");

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
	
	lr_end_transaction("UC04_LogIn_02LogIn",LR_AUTO);
	
	lr_think_time(2);

	lr_start_transaction("UC04_LogIn_03ClickFlights");

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

	web_reg_save_param_attrib(
		"ParamName=departDate",
		"TagName=input",
		"Extract=value",
		"Name=departDate",
		"Type=text",
		SEARCH_FILTERS,
		"RequestUrl=*/reservations.pl*",
		LAST);

	web_reg_save_param_attrib(
		"ParamName=returnDate",
		"TagName=input",
		"Extract=value",
		"Name=returnDate",
		"Type=text",
		SEARCH_FILTERS,
		"RequestUrl=*/reservations.pl*",
		LAST);
	
	web_reg_find("Text=User has returned to the search page", LAST);
	
	web_url("welcome.pl_2", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?page=search", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t244.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC04_LogIn_03ClickFlights",LR_AUTO);
	
	lr_think_time(2);
	
	lr_start_transaction("UC04_LogIn_04FillingFields");

	web_add_auto_header("Origin", 
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

	web_reg_find("Text=Flight departing from", LAST);
	
	web_submit_data("reservations.pl", 
		"Action={protocol}://{host}:{port}/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t247.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=advanceDiscount", "Value=0", ENDITEM, 
		"Name=depart", "Value={departure_city}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={arrival_city}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seating_preference}", ENDITEM, 
		"Name=seatType", "Value={type_of_seat}", ENDITEM, 
		"Name=findFlights.x", "Value=38", ENDITEM, 
		"Name=findFlights.y", "Value=8", ENDITEM, 
		"Name=.cgifields", "Value=roundtrip", ENDITEM, 
		"Name=.cgifields", "Value=seatType", ENDITEM, 
		"Name=.cgifields", "Value=seatPref", ENDITEM, 
		LAST);
	
	lr_end_transaction("UC04_LogIn_04FillingFields",LR_AUTO);

	lr_think_time(2);

	lr_start_transaction("UC04_LogIn_05SignOff");

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

	lr_end_transaction("UC04_LogIn_05SignOff",LR_AUTO);
	
	lr_end_transaction("MAIN_UC04_LogIn",LR_AUTO);

	return 0;
}