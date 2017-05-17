#include "BuyWeapon.h"
#include "stdafx.h"

BuyWeapon::BuyWeapon(load_models * models)
{
	pressed = false;
	collision = 100;
	this->models = models;

	bronie[0].position = { -2,0,5 };
	bronie[0].ammo_cost = 300;
	bronie[0].cost = 600;
	bronie[0].name = "MP5K";

	bronie[1].position = { 3.5,0,-9 };
	bronie[1].ammo_cost = 400;
	bronie[1].cost = 900;
	bronie[1].name = "M4A4";

	bronie[2].position = { -2,0,-4 };
	bronie[2].ammo_cost = 300;
	bronie[2].cost = 650;
	bronie[2].name = "AKS74U";

	bronie[3].position = { 1,0,9 };
	bronie[3].ammo_cost = 350;
	bronie[3].cost = 900;
	bronie[3].name = "SCARH";

	bronie[4].position = { -6,0,10 };
	bronie[4].ammo_cost = 200;
	bronie[4].cost = 400;
	bronie[4].name = "M9";

	bronie[5].position = { -6,0,3 };
	bronie[5].ammo_cost = 400;
	bronie[5].cost = 800;
	bronie[5].name = "AUG";

	bronie[6].position = { -2,0,9 };
	bronie[6].ammo_cost = 600;
	bronie[6].cost = 2000;
	bronie[6].name = "M249";

	bronie[7].position = { -7.25,0,-6 };
	bronie[7].ammo_cost = 400;
	bronie[7].cost = 1200;
	bronie[7].name = "DESERTDEAGLE";

	bronie[8].position = { -5,0,-4 };
	bronie[8].ammo_cost = 350;
	bronie[8].cost = 850;
	bronie[8].name = "BIZON";

	bronie[9].position = { -1.25,0,0 };
	bronie[9].ammo_cost = 10000000;
	bronie[9].cost = 3500;
	bronie[9].name = "BLASTER";


}

void BuyWeapon::Render()
{
	glPushMatrix();
	glTranslatef(bronie[0].position.x, bronie[0].position.y + 0.5 + sin(T*0.001) / 15, bronie[0].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->MP5K_texture->GetId());
	glCallList(models->MP5K);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[1].position.x, bronie[1].position.y + 0.5 + sin(T*0.001) / 15, bronie[1].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->M4A4_texture->GetId());
	glCallList(models->M4A4);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[2].position.x, bronie[2].position.y + 0.5 + sin(T*0.001) / 15, bronie[2].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->AKS74U_texture->GetId());
	glCallList(models->AKS74U);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[3].position.x, bronie[3].position.y + 0.5 + sin(T*0.001) / 15, bronie[3].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->SCARH_texture->GetId());
	glCallList(models->SCARH);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[4].position.x, bronie[4].position.y + 0.5 + sin(T*0.001) / 15, bronie[4].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->M9_texture->GetId());
	glCallList(models->M9);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[5].position.x, bronie[5].position.y + 0.5 + sin(T*0.001) / 15, bronie[5].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->AUG_texture->GetId());
	glCallList(models->AUG);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[6].position.x, bronie[6].position.y + 0.5 + sin(T*0.001) / 15, bronie[6].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->M249_texture->GetId());
	glCallList(models->M249);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[7].position.x, bronie[7].position.y + 0.5 + sin(T*0.001) / 15, bronie[7].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->DesertDeagle_texture->GetId());
	glCallList(models->DesertDeagle);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[8].position.x, bronie[8].position.y + 0.5 + sin(T*0.001) / 15, bronie[8].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->Bizon_texture->GetId());
	glCallList(models->Bizon);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(bronie[9].position.x, bronie[9].position.y + 0.5 + sin(T*0.001) / 15, bronie[9].position.z);
	glScalef(1.8, 1.8, 1.8);
	glRotatef(T*0.03, 0, 1, 0);
	glBindTexture(GL_TEXTURE_2D, models->Blaster_texture->GetId());
	glCallList(models->Blaster);
	glPopMatrix();

}

void BuyWeapon::Update(CPlayer *gracz)
{
	if (collision != 100 && gracz->actual_weapon->shooting == false && gracz->actual_weapon->reloading == false) {
		string name;
		if (gracz->second_slot == NULL)
			name = "NO";
		else
			name = gracz->second_slot->name;
		if (keystate['f'] && pressed == false) {

			if (gracz->first_slot != NULL || gracz->second_slot != NULL)
			{

				pressed = true;

				if (gracz->first_slot->name == bronie[collision].name || name == bronie[collision].name)
				{
					//Jezeli ma pieniadze na amunicje
					if (gracz->money >= bronie[collision].ammo_cost)
					{
						if (gracz->first_slot->name == bronie[collision].name)
						{
								gracz->money -= bronie[collision].ammo_cost;
								gracz->first_slot->current_ammo_magazine = gracz->first_slot->max_ammo_magazine;
								gracz->first_slot->current_ammo = gracz->first_slot->max_ammo;
						}
						if(gracz->second_slot != NULL)
						if (gracz->second_slot->name == bronie[collision].name)
						{

								gracz->money -= bronie[collision].ammo_cost;
								gracz->second_slot->current_ammo_magazine = gracz->second_slot->max_ammo_magazine;
								gracz->second_slot->current_ammo = gracz->second_slot->max_ammo;

							}
						}

					}
				else
				{
					if (gracz->second_slot == NULL) {
						if (gracz->money >= bronie[collision].cost)
						{

							cout << "DLA DRUGIEGO SLOTU\n";
							switch (collision) {
							case 0: gracz->second_slot = new MP5K; break;
							case 1: gracz->second_slot = new M4A4; break;
							case 2: gracz->second_slot = new AK74U; break;
							case 3: gracz->second_slot = new SCARH;  break;
							case 4: gracz->second_slot = new M9;  break;
							case 5: gracz->second_slot = new AUG;  break;
							case 6: gracz->second_slot = new M249;  break;
							case 7: gracz->second_slot = new DESERTDEAGLE; break;
							case 8: gracz->second_slot = new BIZON; break;
							case 9: gracz->second_slot = new BLASTER;  break;

							}
							gracz->money -= bronie[collision].cost;
						}


					}
					else
					{
						if (gracz->actual_weapon == gracz->first_slot)
						{
							weapon *tmp = gracz->actual_weapon;
							if (gracz->money >= bronie[collision].cost)
							{
								switch (collision) {
								case 0: gracz->actual_weapon = new MP5K; gracz->first_slot = gracz->actual_weapon; break;
								case 1: gracz->actual_weapon = new M4A4; gracz->first_slot = gracz->actual_weapon; break;
								case 2: gracz->actual_weapon = new AK74U; gracz->first_slot = gracz->actual_weapon; break;
								case 3: gracz->actual_weapon = new SCARH; gracz->first_slot = gracz->actual_weapon;  break;
								case 4: gracz->actual_weapon = new M9; gracz->first_slot = gracz->actual_weapon;  break;
								case 5: gracz->actual_weapon = new AUG; gracz->first_slot = gracz->actual_weapon;  break;
								case 6: gracz->actual_weapon = new M249; gracz->first_slot = gracz->actual_weapon;  break;
								case 7: gracz->actual_weapon = new DESERTDEAGLE; gracz->first_slot = gracz->actual_weapon; break;
								case 8: gracz->actual_weapon = new BIZON; gracz->first_slot = gracz->actual_weapon; break;
								case 9: gracz->actual_weapon = new BLASTER; gracz->first_slot = gracz->actual_weapon;  break;

								}
								delete tmp;
								gracz->money -= bronie[collision].cost;
							}

						}
						else
						{
							weapon *tmp = gracz->actual_weapon;
							if (gracz->money >= bronie[collision].cost)
							{
								switch (collision) {
								case 0: gracz->actual_weapon = new MP5K; gracz->second_slot = gracz->actual_weapon; break;
								case 1: gracz->actual_weapon = new M4A4; gracz->second_slot = gracz->actual_weapon; break;
								case 2: gracz->actual_weapon = new AK74U; gracz->second_slot = gracz->actual_weapon; break;
								case 3: gracz->actual_weapon = new SCARH; gracz->second_slot = gracz->actual_weapon;  break;
								case 4: gracz->actual_weapon = new M9; gracz->second_slot = gracz->actual_weapon;  break;
								case 5: gracz->actual_weapon = new AUG; gracz->second_slot = gracz->actual_weapon;  break;
								case 6: gracz->actual_weapon = new M249; gracz->second_slot = gracz->actual_weapon;  break;
								case 7: gracz->actual_weapon = new DESERTDEAGLE; gracz->second_slot = gracz->actual_weapon; break;
								case 8: gracz->actual_weapon = new BIZON; gracz->second_slot = gracz->actual_weapon; break;
								case 9: gracz->actual_weapon = new BLASTER; gracz->second_slot = gracz->actual_weapon;  break;

								}
								delete tmp;
								gracz->money -= bronie[collision].cost;
							}
						}
						}

					}

				}
					
		}
		if (!keystate['f'])
		{
			pressed = false;
		}


}



	for (int i = 0; i < 10; i++)
	{
		if (abs(bronie[i].position.x - gracz->pos.x) < 0.4 && abs(bronie[i].position.z - gracz->pos.z) < 0.4) {
			
			collision = i;
			return;
		}
	}
	collision = 100;


}
