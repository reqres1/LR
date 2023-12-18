SignUp()
{
	char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    int length = 11;
    int i;
    int index;
    char result[12];
    char generatedusername[12];
		
    lr_start_transaction("MAIN_UC03_SignUp");
    
	lr_start_transaction("UC03_SignUp_01MainWelcomePage");

	web_add_header("Sec-Fetch-Dest", 
		"document");

	web_add_header("Sec-Fetch-Site", 
		"none");

	web_add_auto_header("Sec-Fetch-Mode", 
		"navigate");

	web_add_header("Sec-Fetch-User", 
		"?1");

	web_add_auto_header("Upgrade-Insecure-Requests", 
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

	lr_end_transaction("UC03_SignUp_01MainWelcomePage",LR_AUTO);

	lr_think_time(2);

	lr_start_transaction("UC03_SignUp_02ClickSignUp");

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

	web_reg_find("Text=Please choose a username and password", LAST);
	
	web_url("login.pl", 
		"URL={protocol}://{host}:{port}/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/WebTours/home.html", 
		"Snapshot=t332.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_SignUp_02ClickSignUp",LR_AUTO);

	lr_think_time(2);

	lr_start_transaction("UC03_SignUp_03FillingFields");

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

	web_reg_find("Text=Click below when you're ready to plan your dream trip", LAST);
	
	srand((unsigned int)time(NULL)); // Инициализация генератора случайных чисел

    for (i = 0; i < length; i++) {
        index = rand() % (sizeof(charset) - 1);
        result[i] = charset[index];
    }

    result[length] = '\0'; // Завершающий нулевой символ
    
    lr_save_string(result, "generatedusername");
	
	web_submit_data("login.pl_2", 
		"Action={protocol}://{host}:{port}/cgi-bin/login.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t339.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={generatedusername}", ENDITEM, 
		"Name=password", "Value={generatedusername}", ENDITEM, 
		"Name=passwordConfirm", "Value={generatedusername}", ENDITEM, 
		"Name=firstName", "Value=", ENDITEM, 
		"Name=lastName", "Value=", ENDITEM, 
		"Name=address1", "Value=", ENDITEM, 
		"Name=address2", "Value=", ENDITEM, 
		"Name=register.x", "Value=43", ENDITEM, 
		"Name=register.y", "Value=11", ENDITEM, 
		LAST);

	lr_end_transaction("UC03_SignUp_03FillingFields",LR_AUTO);

	lr_think_time(2);

	lr_start_transaction("UC03_SignUp_04ClickContinue");

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

	web_reg_find("Text=Using the menu to the left", LAST);
	
	web_url("welcome.pl_3", 
		"URL={protocol}://{host}:{port}/cgi-bin/welcome.pl?page=menus", 
		"TargetFrame=", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer={protocol}://{host}:{port}/cgi-bin/login.pl", 
		"Snapshot=t342.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("UC03_SignUp_04ClickContinue",LR_AUTO);

	lr_start_transaction("UC03_SignUp_05SignOff");

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

	lr_end_transaction("UC03_SignUp_05SignOff",LR_AUTO);
	
	lr_end_transaction("MAIN_UC03_SignUp",LR_AUTO);

	return 0;
}
