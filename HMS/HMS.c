#include<stdio.h>/*After scanf() and before gets() to prevent the newline issue===>use fflush(stdin);*/
#include<string.h>
struct Patient{
	char name[50];
	char password[50];
	char login[50];
	char ragister[50];
	char decies[50];
	char last_decies[50];//view history decies
	int room_no;//Between 1 to 50
	int last_room_no;//view history room_no
	char date[50];
	char last_date[50];//view history date
	char select_doctor[50];//for appintment
	int medical_amount;//this is use in Generate Billing Report
};
struct Admin{
	char name[50];
	char password[50];
	char login[50];	
};
struct Doctor{
	char name[50];
	char e_mail[50];
	long emergency_number;/*%ld*/	
	char specialist[50];
	char isolated_meeting[100];
	int  isolated_meeting_room_no;/*51 to 60 Between*/
	char walk_ins[50];
	int call_shift;
	float operation_hour;
};
int Add_Patient(){
	int n;
	printf("Enter How Many Patients You want to Add:");
	scanf("%d",&n);
	fflush(stdin);
	printf("Now Adding %d Patients.",n);
	return n;
}
int Delete_Patient(){
	int n;
	printf("Enter How Many Patients You want to Delete:");
	scanf("%d",&n);
	fflush(stdin);
	printf("Now Deleting %d Patients.",n);
	return n;
}
void main()
{
	int i1=0/*For the Admins++*/,j1=0/*For the Patients++*/,k1=0/*For Doctor Info while Loop*/,l1=0/*Add Doctor Schedual*/,r1=0/*for room updating*/,r0=0/*for room counting*/,rsum=0/*for doing sum of rooms*/,dashboard_option=0;
	int i2=0/*Update patients Details,View,Schedule Appointment,Cancel Appointment for Doctors,View Appointments for Admin*/,j2=0,k2=0;
	char password_check[50];//use for admin and patient for comparing their password
	char person_role[50];
	char new_old_check[50];
	struct Doctor doctors[4];
	FILE *fptr1,*fptr2;
	fptr1 = fopen("Admins.txt","a");
	fptr2 = fopen("Patients.txt","a");
	fputs("ADMINS LIST:\n\n",fptr1);
	fputs("PATIENTS LIST:\n\n",fptr2);
	printf("\n\n\t\t\tWELCOME TO THE Hospital Management System (HMS) APP.\n\nFirst Enter Info About Hospital's Main 4 Doctors..\n");
	do
	{
		printf("\nEnter doctors[%d].name :",k1);
		gets(doctors[k1].name);
		printf("Enter doctors[%d].emergency_number:",k1);
		scanf("%ld",&doctors[k1].emergency_number);
		fflush(stdin);
		printf("Enter doctors[%d].specialist :",k1);
		gets(doctors[k1].specialist);
		fflush(stdin);
		printf("Enter doctors[%d].e_mail :",k1);
		gets(doctors[k1].e_mail);
		fflush(stdin);
		k1++;
	}while(k1!=4);
	int tolal_admins=0;
	printf("\nHow many Admin Staff You Want to Add: ");
	scanf("%d",&tolal_admins);
	fflush(stdin);
	struct Admin admins[tolal_admins];
	int tolal_patients=0;
	printf("How many Patients You Want to Add: ");
	scanf("%d",&tolal_patients);
	fflush(stdin);
	int patient_count1=tolal_patients;
	int	patient_count2=0;
	struct Patient patients[tolal_patients];
	int room[tolal_patients];
	for(r1=0;r1<tolal_patients;r1++){//50 Rooms Held in Hospital, 1= availabe , 0=non-available 
		room[r1]=1;
	}
	do
	{
		printf("\n\n1. Admin\n2. Patients\n3. Exit \nEnter Who are You?:");
		gets(person_role);
		if(strcmp(person_role,"Admin")==0){
			fflush(stdin);
			printf("Are You New or Old Admin:");
			gets(new_old_check);
			if(strcmp(new_old_check,"New")==0){
				printf("Enter admins[%d] name:",i1);
				gets(admins[i1].name);
				fflush(stdin);
				printf("Enter admins[%d] login:",i1);
				gets(admins[i1].login);
				fflush(stdin);
				printf("Enter admins[%d] password:",i1);
				gets(admins[i1].password);
				fprintf(fptr1,"%d. ",(i1+1));
				fputs("Name:",fptr1);
				fputs(admins[i1].name,fptr1);
				fputs("==>Login:",fptr1);
				fputs(admins[i1].login,fptr1);
				fputs("==>Password:",fptr1);
				fputs(admins[i1].password,fptr1);
				fputs("\n",fptr1);
				i1++;
			}
			else if(strcmp(new_old_check,"Old")==0){
				printf("Enter Admin Number From 0 to %d:",(i1-1));
				scanf("%d",&i2);
				fflush(stdin);
				printf("Enter admins[%d].password:",i2);
				gets(password_check);
				if(strcmp(password_check,admins[i2].password)!=0){
					printf("Sorry, %s You Enter Invalid Password.",admins[i2].name);
					continue;
				}
				/* password_check[50];*/
				printf("\nHello %s. Welcome Again in HMS Portal.",admins[i2].name);
			}	
				printf("\n\nADMIN STAFF DASHBOARD\n\n");
				do
				{
					printf("\n\nOptions:\n1.Add Patient\n2.Delete Patient\n3.Update Patient Details\n4.View Patient Details\n5.Schedule Appointment\n6.Cancel Appointment\n7.View Appointments\n8.Add Doctor Schedule\n9.Delete Doctor Schedule\n10.View Doctor Details\n11.View Room Availability\n12.Allocate Room\n13.Release Room\n14.Generate Billing Report\n15.Logout\n\n");
					printf("Select Index Number:");
					scanf("%d",&dashboard_option);
					fflush(stdin);
				if(dashboard_option==1){
					patient_count2+=Add_Patient();
					printf("\nNow Total Patients ===> %d\n",patient_count2);	
				}
				else if(dashboard_option==2){
					patient_count2-=Delete_Patient();
					printf("\nNow Total Patients ===> %d\n",patient_count2);
				}
				else if(dashboard_option==3){
					/*Update patients Details*/
					printf("Enter Patient Index For Them:"); 
					scanf("%d",&i2);
					fflush(stdin);
					printf("Ohh! You Want to Update Details of %s.\n",patients[i2].name);
				    strcpy(patients[i2].last_date,patients[i2].date);
					printf("Enter %s New Date:",patients[i2].name);
					gets(patients[i2].date);
					patients[i2].last_room_no=patients[i2].room_no;
					printf("Enter %s New Room Number(1 to %d):",patients[i2].name,tolal_patients);
					scanf("%d",&patients[i2].room_no);
					fflush(stdin);
					strcpy(patients[i2].last_decies,patients[i2].decies);
					printf("Enter %s New Decies:",patients[i2].name);
					gets(patients[i2].decies);
					printf("\n %s Details Now Update You can Check It Out.\n");
				}
				else if(dashboard_option==4){
					/*4.View Patient Details*/
					printf("Enter Patient Index For Them:");
					scanf("%d",&i2);
					fflush(stdin);
					printf("Patient Name: %s",patients[i2].name);
					printf("\nPatient Decies: %s\n",patients[i2].decies);
					printf("Patient Room Number: %d\n",patients[i2].room_no);
					printf("\nPatient Admit Date: %s\n",patients[i2].date);
					printf("Patient Total Bill: %d\n",patients[i2].medical_amount);
					printf("\nPatient Decies: %s\n",patients[i2].decies);
				}
				else if(dashboard_option==5){
					/*5.Schedule Appointment*/
					printf("Enter Doctor Number(0, 1, 2 or 3) For Schedule Appointment:");
					scanf("%d",&i2);
					fflush(stdin);
					printf("Enter Reason for Dr.%s Isolated Meeting:",doctors[i2].name);
					gets(doctors[i2].isolated_meeting);
					printf("Enter Room No. for Dr.%s Isolated Meeting(from 51 to 60):",doctors[i2].name);
					scanf("%d",&doctors[i2].isolated_meeting_room_no);
					fflush(stdin);
				}
				else if(dashboard_option==6){
					/*Cancel Appointment*/
					printf("Enter Doctor Number(0, 1, 2 or 3) For Cancle Appointment:");
					scanf("%d",&i2);
					fflush(stdin);
					strcpy(doctors[i2].isolated_meeting,"");
					doctors[i2].isolated_meeting_room_no=0;
					printf("Dr.%s  Appointment is Cancle(Clear) Successfully You can Check It Out.\n",doctors[i2].name);
				}
				else if(dashboard_option==7){
					/*View Appointments\n*/
					printf("Enter Doctor Number(0, 1, 2 or 3) For View Appointment:");
					scanf("%d",&i2);
					fflush(stdin);
					printf("Dr.%s Isolated Meeting in This Time: %s\n",doctors[i2].name,doctors[i2].isolated_meeting);
					printf("Dr.%s Isolated Meeting Room No. in This Time: %s\n",doctors[i2].name,doctors[i2].isolated_meeting_room_no);					
				}
				else if(dashboard_option==8){
					/*n8.Add Doctor Schedule*/
					/*D.S: patient schedule, walk-ins, call-shift, operation_hour*/
					printf("Enter Doctor Number(0, 1, 2 or 3) For Add Doctor Schedule:");
					scanf("%d",&l1);
					fflush(stdin);					
					printf("Ask Dr.%s to Which Number Patient(0 to %d) Schedule they Want to Watch:",doctors[l1].name,(j1-1));
					scanf("%d",&i2);
					fflush(stdin);
					printf("\nPatient Name: %s",patients[i2].name);
					printf("\nPatient Decies: %s",patients[i2].decies);
					printf("\nPatient Room No: %d",patients[i2].room_no);
					printf("\nPatient Admit Date: %s",patients[i2].date);
					printf("\nEnter Doctor Walk-Ins(Require or Not Require):");
					gets(doctors[l1].walk_ins);
					printf("Enter How many Call-Shift Require for Doctor:");
					scanf("%d",&doctors[l1].call_shift);
					fflush(stdin);
					printf("Enter How many Operation Hour Require for Doctor: ");
					scanf("%f",&doctors[l1].operation_hour);
					fflush(stdin);
				}
				else if(dashboard_option==9){
				/*\n9.Delete Doctor Schedule*/
					printf("Enter Doctor Number(0, 1, 2 or 3) For Delete Doctor Schedule:");
					scanf("%d",&l1);
					fflush(stdin);
					strcpy(doctors[l1].walk_ins,"");
					doctors[l1].call_shift=0;
					doctors[l1].operation_hour=0.0;
					printf("\nDr.%s  Schedule is Delete Successfully You can Check It Out.\n",doctors[l1].name);					
				}
				else if(dashboard_option==10){
					/*\n10.View Doctor Details*/
					printf("Enter Doctor Number(0, 1, 2 or 3) For View Doctor Details:");
					scanf("%d",&l1);
					fflush(stdin);
					printf("\nDoctor Name: %s",doctors[l1].name);
					printf("\n%s Emergency Number: %ld",doctors[l1].name,doctors[l1].emergency_number);
					printf("\n%s Specialist: %s",doctors[l1].name, doctors[l1].specialist);
					printf("\n%s E-mail: %s",doctors[l1].name,doctors[l1].e_mail );
				}
				else if(dashboard_option==11){
					/*\n11.View Room Availability*/
				/*r1=0for room updating,r0=0for room counting,rsum=0for doing sum of rooms*/
					r1=0;
					for(r0=0;r0<tolal_patients;r0++){
                      	r1+=room[r0];		
					}
					printf("Here Total Room Availability(from %d) is: %d\n",tolal_patients,r1);
				}
				else if(dashboard_option==12){
					/*\n12.Allocate Room*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to Allocate Room:",j1-1);
					scanf("%d",&i2);
					fflush(stdin);
					for(r0=0;r0<tolal_patients;r0++){
						if(room[r0]==1){
							room[r0]=0;
							printf("Patient %s Allocate Room is: %d\n",patients[i2].name,r0+1);
							patients[i2].room_no=r0+1;
							break;
						}	
					}
				}
				else if(dashboard_option==13){
					/*\n13.Release Room*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to Release Room:",j1-1);
					scanf("%d",&i2);
					fflush(stdin);
					if(room[i2]==0){
						room[i2]=1;
						patients[i2].room_no=0;
						printf("Patient %s Release Room is: %d\n",patients[i2].name,i2+1);
					}
				}
				else if(dashboard_option==14){
				/*\n14.Generate Billing Report*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to Generate Billing Report:",j1-1);
					scanf("%d",&i2);
					fflush(stdin);
					fprintf(fptr2,"%d. ",i2);
					fputs("Name:",fptr2);
					fputs(patients[i2].name,fptr2);
					fputs("==>Login:",fptr2);
					fputs(patients[i2].login,fptr2);
					fputs("==>Register:",fptr2);
					fputs(patients[i2].ragister,fptr2);
					fputs("==>Password:",fptr2);
					fputs(patients[i2].name,fptr2);
					fputs("==>Room No:",fptr2);
					fprintf(fptr2,"%d",patients[i2].room_no);
					fputs("==>Admit Date:",fptr2);
					fputs(patients[i2].date,fptr2);
					fputs("==>Decies:",fptr2);
					fputs(patients[i2].decies,fptr2);					
					patients[i2].medical_amount=(patients[i2].room_no*100*(i2+1));
					fputs("==>Total Amount:",fptr2);
					fprintf(fptr2,"%d",patients[i2].medical_amount);
					fputs("\n",fptr2);
					printf("Patient %s Total Billing Report: %dRs.\n",patients[i2].name,patients[i2].medical_amount);
				}
				else if(dashboard_option==15){
					/*\n15.Logout*/
					fflush(stdin);
					break;
				}
			}while(1);				
		}
		else if(strcmp(person_role,"Patients")==0){
			printf("Are You New or Old Patients:");
			gets(new_old_check);
			fflush(stdin);
			if(strcmp(new_old_check,"New")==0){
				printf("Enter patients[%d] name:",j1);
				gets(patients[j1].name);
				fflush(stdin);
				printf("Enter patients[%d] date:",j1);
				gets(patients[j1].date);
				fflush(stdin);
				printf("Enter patients[%d] login:",j1);
				gets(patients[j1].login);
				fflush(stdin);
				printf("Enter patients[%d] register:",j1);
				gets(patients[j1].ragister);
				fflush(stdin);	
				printf("Enter patients[%d] password:",j1);
				gets(patients[j1].password);
				/*v/*char decies[50];*/
				fflush(stdin);
				printf("Enter patients[%d] decies name:",j1);
				gets(patients[j1].decies);
				j1++;
			}
			else if(strcmp(new_old_check,"Old")==0){
				printf("Enter Patient Number From 0 to %d:",(j1-1));
				scanf("%d",&j2);
				fflush(stdin);
			 	printf("Enter Patient[%d].password:",j2);
				gets(password_check);
				if(strcmp(password_check,patients[j2].password)!=0){
					printf("Sorry, %s You Enter Invalid Password.",patients[j2].name);
					continue;
				}
				/* password_check[50];*/
				printf("Hello %s. Welcome Again in HMS Portal.",patients[j2].name);
			}
			printf("\n\nPATIENT DASHBOARD\n\n");	
			do
			{
				printf("\n\nOptions:\n1.View Personal Details\n2.Book Appointment\n3.Cancel Appointment\n4.View Visit History\n5.View Room Status\n6.View Billing Information\n7.Logout\n\n");
				printf("Select Index Number:");
				scanf("%d",&dashboard_option);
				fflush(stdin);
				if(dashboard_option==1){
					/*\n1.View Personal Details*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to view Personal Details:",j1-1);
					scanf("%d",&j2);
					fflush(stdin);
					printf("\nPatient Name: %s",patients[j2].name);
					printf("\nPatient Decies: %s",patients[j2].decies);
					printf("\nPatient Room No: %d",patients[j2].room_no);
					printf("\nPatient Admit Date: %s",patients[j2].date);
					printf("\nPatient Medical Amount: %d\n",patients[j2].medical_amount);
				}
				else if(dashboard_option==2){
					/*\n2.Book Appointment*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to Book Appointment:",j1-1);
					scanf("%d",&j2);
					fflush(stdin);
					for(k2=0;k2<4;k2++){
						printf("%d. Dr.%s\n",k2,doctors[k2].name);
					}
					printf("For %s , Which Doctor Index You Want to Select For Appoitment:",patients[j2].name);
					scanf("%d",&j2);
					fflush(stdin);
					strcpy(patients[j2].select_doctor,doctors[j2].name);
					printf("\nGiven Patient %s Appointment making Succesfully by Dr.%s.\n",patients[j2].name,doctors[j2].name);
					/*char select_doctor[50];*/
					
				}
				else if(dashboard_option==3){
					/*3.Cancel Appointment*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to Cancle Appointment:",j1-1);
					scanf("%d",&j2);
					fflush(stdin);
					strcpy(patients[j2].select_doctor,"");
					printf("\nGiven Patient %s Appointment Cancling Succesfully.\n",patients[j2].name);
				}
				else if(dashboard_option==4){
					/*\n4.View Visit History*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to Visit History:",j1-1);
					scanf("%d",&j2);
					fflush(stdin);
					printf("\nPatient %s Last Decies: %s",patients[j2].name,patients[j2].last_decies);
					printf("\nPatient %s Room No: %d",patients[j2].name,patients[j2].last_room_no);
					printf("\nPatient %s Admit Date: %s",patients[j2].name,patients[j2].last_date);
				}
				else if(dashboard_option==5){
					/*\n5.View Room Status*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to View Room Status:",j1-1);
					scanf("%d",&j2);
					fflush(stdin);
					printf("Patient %s Room No: %d",patients[j2].name,patients[j2].room_no);
					r1=0;
					for(r0=0;r0<50;r0++){
                      	r1+=room[r0];		
					}
					printf("\nHere Total Room Availability(from %d) is: %d\n",tolal_patients,r1);					
				}
				else if(dashboard_option==6){
				/*\n6.View Billing Information*/
					printf("Enter For Which Number Patient(0 to %d) For You Want to View Billing Information:",j1-1);
					scanf("%d",&j2);
					fflush(stdin);
					printf("Patient %s Total Billing Report: %dRs.\n",patients[j2].name,patients[j2].medical_amount);
				}
				else if(dashboard_option==7){
					/*\n7.Logout*/
					fflush(stdin);
					break;
				}	
			}while(1);											
		}
		else{
		//3. Exit
			break;
		}
	}while(1);
	fclose(fptr1);
	fclose(fptr2);
	printf("\n\n\t\tTHANKS FOR VISITING HMS APPLICATION....\n\n");
}
