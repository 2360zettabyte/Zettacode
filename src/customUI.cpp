#include "main.h"
#include "MyHeaders/global.h"


std::string contText = "";
bool redTeam;
void UIFunc(){
	pros::lcd::shutdown(); //disables default Screen
	pros::Controller main(pros::E_CONTROLLER_MASTER); //Creates an object of the main controller
	std::string autonNum = "-0-"; //String that will be used for the

//--STYLES--//
lv_style_t defaultStyle;
lv_style_copy(&defaultStyle, &lv_style_pretty);    /*Copy a built-in style to initialize the new style*/
defaultStyle.body.main_color = LV_COLOR_MAKE(20, 20, 20);
defaultStyle.body.grad_color = LV_COLOR_MAKE(20, 20, 20);
defaultStyle.body.radius = 10;
defaultStyle.body.border.color = LV_COLOR_MAKE(255, 255, 255);
defaultStyle.body.border.width = 3;
defaultStyle.body.border.opa = LV_OPA_100;
defaultStyle.text.color = LV_COLOR_MAKE(255, 255, 255);

lv_style_t screenStyle;
lv_style_copy(&screenStyle, &defaultStyle);    /*Copy a built-in style to initialize the new style*/
screenStyle.body.main_color = LV_COLOR_MAKE(20, 20, 20);
screenStyle.body.grad_color = LV_COLOR_MAKE(20, 20, 20);
screenStyle.body.border.width = 0;

lv_style_t buttonOn;
lv_style_copy(&buttonOn, &defaultStyle);    /*Copy a built-in style to initialize the new style*/
buttonOn.body.main_color = LV_COLOR_MAKE(255, 255, 255);
buttonOn.body.grad_color = LV_COLOR_MAKE(255, 255, 255);

lv_style_t teamStyle;
lv_style_copy(&teamStyle, &defaultStyle);    /*Copy a built-in style to initialize the new style*/
teamStyle.body.main_color = LV_COLOR_MAKE(255, 0, 0);
teamStyle.body.grad_color = LV_COLOR_MAKE(255, 0, 0);

lv_style_t teamStyleOff;
lv_style_copy(&teamStyleOff, &defaultStyle);    /*Copy a built-in style to initialize the new style*/
teamStyleOff.body.main_color = LV_COLOR_MAKE(200, 0, 0);
teamStyleOff.body.grad_color = LV_COLOR_MAKE(200, 0, 0);



	lv_obj_t * scr = lv_obj_create(NULL, NULL);
	lv_obj_set_style(scr, &screenStyle);
	lv_scr_load(scr);

	lv_obj_t *description = lv_label_create(lv_scr_act(),NULL); //label
	lv_label_set_recolor(description, true);
	lv_obj_set_pos(description, 30,180);
	lv_label_set_text(description,"#fcba03 2360 Zettabyte#");

	lv_obj_t *currentAuton = lv_label_create(lv_scr_act(),NULL); //label
	lv_obj_set_pos(currentAuton, 320,10);
	lv_obj_set_style(currentAuton, &defaultStyle);
	lv_label_set_text(currentAuton,autonNum.c_str());

	lv_obj_t * prev = lv_btn_create(scr, NULL);
	lv_obj_set_style(prev, &defaultStyle);
	lv_obj_set_size(prev, 45, 45);

	lv_btn_set_style(prev, LV_BTN_STYLE_REL, &defaultStyle);
	lv_btn_set_style(prev, LV_BTN_STYLE_PR , &buttonOn);
	lv_btn_set_style(prev, LV_BTN_STYLE_TGL_REL , &defaultStyle);
	lv_btn_set_style(prev, LV_BTN_STYLE_TGL_PR , &buttonOn);
	lv_btn_set_style(prev, LV_BTN_STYLE_INA , &defaultStyle);

	lv_obj_set_pos(prev, 430, 110);

	lv_obj_t * next = lv_btn_create(scr, prev);
	lv_obj_set_pos(next, 430, 50);

	lv_obj_t * teamBtn = lv_btn_create(scr, prev);
	lv_obj_set_pos(teamBtn, 410, 190);
	lv_btn_set_fit(teamBtn, true, true);
	lv_btn_set_style(teamBtn, LV_BTN_STYLE_REL, &teamStyle);
	lv_btn_set_style(teamBtn, LV_BTN_STYLE_PR , &teamStyleOff);
	lv_btn_set_style(teamBtn, LV_BTN_STYLE_TGL_REL , &teamStyle);
	lv_btn_set_style(teamBtn, LV_BTN_STYLE_TGL_PR , &teamStyleOff);
	lv_btn_set_style(teamBtn, LV_BTN_STYLE_INA , &teamStyle);

	lv_obj_t * prevLbl = lv_label_create(prev, NULL);
	lv_label_set_text(prevLbl, "-");

	lv_obj_t * nextLbl = lv_label_create(next, NULL);
	lv_label_set_text(nextLbl, "+");

	lv_obj_t * teamLbl = lv_label_create(teamBtn, NULL);

	lv_label_set_text(teamLbl, "TEAM");

	//UI infinite loop
	while(true){ //infinite loop

		if(mainAuton<12&&lv_btn_get_state(next)==1){	mainAuton++; } //NEXT Button
		if(mainAuton>0&&lv_btn_get_state(prev)==1){ mainAuton--; } //PREV Button
		if(lv_btn_get_state(teamBtn)==1){
			redTeam= !redTeam;
		} //Team Toggle Button

		if(redTeam == true){
			teamStyle.body.main_color = LV_COLOR_MAKE(255, 0, 0);
			teamStyle.body.grad_color = LV_COLOR_MAKE(255, 0, 0);
			teamStyleOff.body.main_color = LV_COLOR_MAKE(200, 0, 0);
			teamStyleOff.body.grad_color = LV_COLOR_MAKE(200, 0, 0);
			lv_obj_refresh_style(teamBtn);

		}else{
			teamStyle.body.main_color = LV_COLOR_MAKE(0, 0, 255);
			teamStyle.body.grad_color = LV_COLOR_MAKE(0, 0, 255);
			teamStyleOff.body.main_color = LV_COLOR_MAKE(0, 0, 200);
			teamStyleOff.body.grad_color = LV_COLOR_MAKE(0, 0, 200);
			lv_obj_refresh_style(teamBtn);
		}

		autonNum = "Autonomous: " + std::to_string(mainAuton) + "";

		lv_label_set_text(currentAuton,autonNum.c_str());




		//main.set_text(2, 1, contText.c_str()); //Controller debugging screen
		pros::delay(500);
	}
}


/*HOW TO string
std::string text = "FlyWheel: "+ std::to_string(flywheel.get_actual_velocity()) + " RPM";
contConsole(text.c_str());
*/
