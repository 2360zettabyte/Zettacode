#include "main.h"
#include "MyHeaders/global.h"

std::string contText = "";
bool redTeam;
void UIFunc(){
	pros::lcd::shutdown(); //disables default Screen
	pros::Controller main(pros::E_CONTROLLER_MASTER); //Creates an object of the main controller
	std::string autonNum = "-0-"; //String that will be used for the

	lv_obj_t * scr = lv_obj_create(NULL, NULL);
	lv_scr_load(scr);

	lv_obj_t *description = lv_label_create(lv_scr_act(),NULL); //label
	lv_obj_set_pos(description, 10,0);
	lv_label_set_text(description,"2360 Zettabyte\n--Descritons Coming Soon--");

	lv_obj_t *currentAuton = lv_label_create(lv_scr_act(),NULL); //label
	lv_obj_set_pos(currentAuton, 180,70);
	lv_label_set_text(currentAuton,autonNum.c_str());

	lv_obj_t * prev = lv_btn_create(scr, NULL);
	lv_btn_set_fit(prev, true, true);
	lv_obj_set_pos(prev, 40, 30);

	lv_obj_t * next = lv_btn_create(scr, prev);
	lv_obj_set_pos(next, 220, 30);

	lv_obj_t * teamBtn = lv_btn_create(scr, prev);
	lv_obj_set_pos(teamBtn, 130, 100);

	lv_obj_t * prevLbl = lv_label_create(prev, NULL);
	lv_label_set_text(prevLbl, "PREV");

	lv_obj_t * nextLbl = lv_label_create(next, NULL);
	lv_label_set_text(nextLbl, "NEXT");

	lv_obj_t * teamLbl = lv_label_create(teamBtn, NULL);
	lv_label_set_text(teamLbl, "--RED--");

	//UI infinite loop
	while(true){ //infinite loop

		if(mainAuton<=12&&lv_btn_get_state(next)==1){	mainAuton++; } //NEXT Button
		if(mainAuton>=0&&lv_btn_get_state(prev)==1){ mainAuton--; } //PREV Button
		if(lv_btn_get_state(teamBtn)==1){ redTeam= !redTeam; } //Team Toggle Button

		if(redTeam == true){
			lv_label_set_text(teamLbl, "--RED--");
		}else{
			lv_label_set_text(teamLbl, "--BLUE--");
		}

		autonNum = "-" + std::to_string(mainAuton) + "-";

		lv_label_set_text(currentAuton,autonNum.c_str());




		//main.set_text(2, 1, contText.c_str()); //Controller debugging screen
		pros::delay(500);
	}
}


/*HOW TO string
std::string text = "FlyWheel: "+ std::to_string(flywheel.get_actual_velocity()) + " RPM";
contConsole(text.c_str());
*/
