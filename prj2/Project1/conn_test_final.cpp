#define _CRT_SECURE_NO_WARNINGS
#define MAXLEN 1024
#include <stdio.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

void init_mysql();
void deinit_mysql();
void handle_query(int);
void handle_type1();
void handle_type1_1();
void handle_type1_2();
void handle_type1_3();
void handle_type2();
void handle_type3();
void handle_type4();
void handle_type5();

const char* host = "localhost";
const char* user = "root";
const char* pw = "Dh990315@";
const char* db = "project2";

MYSQL* connection = NULL;
MYSQL conn;
MYSQL_RES* sql_result;
MYSQL_ROW sql_row;

int main(void) {
	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		printf("Connection Succeed\n");
		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		init_mysql();
		while (1) {
			int type;
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t0. QUIT\n");
			printf("input query number : ");
			scanf("%d", &type);
			if (type == 0) break;
			handle_query(type);
		}
		deinit_mysql();
		mysql_close(connection);
	}

	return 0;
}

void init_mysql() {//execution CREATE table and INSERT values
	char buffer[MAXLEN];
	FILE* fp = fopen("DDL.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	while (1) {
		char* result = fgets(buffer, MAXLEN, fp);
		if (result == NULL) break;
		mysql_query(connection, buffer);
	}
	printf("complete to execute DDL.sql\n");
	fclose(fp);

	fp = fopen("datainsertion.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	while (1) {
		char* result = fgets(buffer, MAXLEN, fp);
		if (result == NULL) break;
		mysql_query(connection, buffer);
	}
	printf("complete to execute dateinsertion.sql\n");
	fclose(fp);
}

void deinit_mysql() {
	char buffer[MAXLEN];
	FILE* fp = fopen("DROP.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	while (1) {
		char* result = fgets(buffer, MAXLEN, fp);
		if (result == NULL) break;
		mysql_query(connection, buffer);
	}
	printf("complete to execute DROP.sql\n");
	fclose(fp);
}

void handle_query(int type) {
	switch (type) {
	case 1:
		handle_type1();//assume truck X is destoryed in a crash
		break;
	case 2:
		handle_type2();//find the customer who has shipped the most packages in the past year
		break;
	case 3:
		handle_type3();//find the customer who has spent the most money on shipping in the past year
		break;
	case 4:
		handle_type4();//find the packages that were not delivered whitin the promised time
		break;
	case 5:
		handle_type5();//generate the bill for each customer for the past month
		break;
	default:
		printf("wrong input\n");
	}
}

void handle_type1() {
	printf("------- Subtypes in TYPE I -------\n\n");
	printf("\t1. TYPE I-1\n");
	printf("\t2. TYPE I-2\n");
	printf("\t3. TYPE I-3\n");
	int type, truckNum;
	while (1) {
		printf("input subquery num : ");
		scanf("%d", &type);
		if (type == 0) break;
		switch (type) {
		case 1:
			handle_type1_1();//find all customers who had a package on the truck at the time of the crash
			break;
		case 2:
			handle_type1_2();//find all recipients who had a package on that truck at the time of the crash
			break;
		case 3:
			handle_type1_3();//find the last successful delivery by that truck prior to the crash
			break;
		default:
			printf("wrong input\n");
		}
	}

}
void handle_type1_1() {
	char query[MAXLEN];
	char buffer[MAXLEN];
	FILE* fp = fopen("type1-1.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	fgets(query, MAXLEN, fp);
	for (int i = 0; query[i] != '\0'; i++) {
		if (query[i] == '\n') query[i] = '\0';
	}
	char user_string[10];
	int truckNum;
	printf("----- TYPE I-1 ------\n\n");
	printf("**find all customers who had a package on the truck at the time of the crash**\n");
	printf("input truckNum : ");
	scanf("%d", &truckNum);
	sprintf(user_string, "%d", truckNum);
	strcat(query, user_string);
	fgets(buffer, MAXLEN, fp);
	strcat(query, buffer);
	fclose(fp);
	int state = 0;
	state = mysql_query(connection, query);
	if (state == 0)
	{
		sql_result = mysql_store_result(connection);

		printf("customer_id\tpackage_id\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
			printf("%s\t%s\n", sql_row[0], sql_row[1]);
		}
		mysql_free_result(sql_result);
	}
}

void handle_type1_2() {
	char query[MAXLEN];
	char buffer[MAXLEN];
	FILE* fp = fopen("type1-2.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	fgets(query, MAXLEN, fp);
	for (int i = 0; query[i] != '\0'; i++) {
		if (query[i] == '\n') query[i] = '\0';
	}
	char user_string[10];
	int truckNum;
	printf("----- TYPE I-2 ------\n\n");
	printf("**find all recipients who had a package on that truck at the time of the crash**\n");
	printf("input truckNum : ");
	scanf("%d", &truckNum);
	sprintf(user_string, "%d", truckNum);
	strcat(query, user_string);
	fgets(buffer, MAXLEN, fp);
	strcat(query, buffer);
	fclose(fp);
	int state = 0;
	state = mysql_query(connection, query);
	if (state == 0)
	{
		sql_result = mysql_store_result(connection);
		printf("destination_address\tpackage_id\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
			printf("%s\t%s\n", sql_row[0], sql_row[1]);
		}
		mysql_free_result(sql_result);
	}
}

void handle_type1_3() {
	char query[MAXLEN];
	char buffer[MAXLEN];
	FILE* fp = fopen("type1-3.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	fgets(query, MAXLEN, fp);
	for (int i = 0; query[i] != '\0'; i++) {
		if (query[i] == '\n') query[i] = '\0';
	}
	char user_string[10];
	int truckNum;
	printf("----- TYPE I-3 ------\n\n");
	printf("**find the last successful delivery by that truck prior to the crash**\n");
	printf("input truckNum : ");
	scanf("%d", &truckNum);
	sprintf(user_string, "%d", truckNum);
	strcat(query, user_string);
	fgets(buffer, MAXLEN, fp);
	strcat(query, buffer);
	fclose(fp);
	int state = 0;
	state = mysql_query(connection, query);
	if (state == 0)
	{
		sql_result = mysql_store_result(connection);

		printf("customer_id\tpackage_id\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
			printf("%s\t%s\n", sql_row[0], sql_row[1]);
		}
		mysql_free_result(sql_result);
	}
}

void handle_type2() {
	char query[MAXLEN];
	char buffer[MAXLEN];
	FILE* fp = fopen("type2.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	fgets(query, MAXLEN, fp);
	for (int i = 0; query[i] != '\0'; i++) {
		if (query[i] == '\n') query[i] = '\0';
	}
	int user_year;
	printf("----- TYPE II ------\n\n");
	printf("**find the customer who has shipped the most packages in the past year**\n");
	printf("input year : ");
	scanf("%d", &user_year);
	user_year--;
	char user_year_string[10];
	sprintf(user_year_string, "%d", user_year);
	strcat(query, user_year_string);
	fgets(buffer, MAXLEN, fp);
	strcat(query, buffer);
	fclose(fp);
	int state = 0;
	state = mysql_query(connection, query);
	if (state == 0)
	{
		sql_result = mysql_store_result(connection);
		printf("customer_id\ttotal_count\tpast_year\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
			printf("%s\t%s\t\t%s\n", sql_row[0], sql_row[1], sql_row[2]);
		}
		mysql_free_result(sql_result);
	}
}

void handle_type3() {
	char query[MAXLEN];
	char buffer[MAXLEN];
	FILE* fp = fopen("type3.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	fgets(query, MAXLEN, fp);
	for (int i = 0; query[i] != '\0'; i++) {
		if (query[i] == '\n') query[i] = '\0';
	}
	int user_year;
	printf("----- TYPE III ------\n\n");
	printf("**find the customer who has spent the most money on shipping in the past year**\n");
	printf("input year : ");
	scanf("%d", &user_year);
	user_year--;
	char user_year_string[10];
	sprintf(user_year_string, "%d", user_year);
	strcat(query, user_year_string);
	fgets(buffer, MAXLEN, fp);
	strcat(query, buffer);
	fclose(fp);
	int state = 0;
	state = mysql_query(connection, query);
	if (state == 0)
	{
		sql_result = mysql_store_result(connection);
		printf("customer_id\ttotal_money\tpast_year\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
			printf("%s\t%s\t\t%s\n", sql_row[0], sql_row[1], sql_row[2]);
		}
		mysql_free_result(sql_result);
	}
}

void handle_type4() {
	char query[MAXLEN];
	FILE* fp = fopen("type4.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	fgets(query, MAXLEN, fp);
	fclose(fp);
	int state = 0;
	state = mysql_query(connection, query);
	if (state == 0)
	{
		sql_result = mysql_store_result(connection);
		printf("----- TYPE IV ------\n\n");
		printf("**find the packages that were not delivered whitin the promised time**\n");
		printf("customer_id\tpackage_id\texpected_arrived_date actual_arrive_date\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
			printf("%s\t%s\t%s\t\t%s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3]);
		}
		mysql_free_result(sql_result);
	}
}

void handle_type5() {
	char query[MAXLEN];
	char buffer[MAXLEN];
	FILE* fp = fopen("type5.sql", "r");
	if (fp == NULL) {
		printf("file open error\n");
		exit(1);
	}
	fgets(query, MAXLEN, fp);
	int user_year, user_month;
	printf("----- TYPE V ------\n\n");
	printf("**generate the bill for each customer for the past month**\n");
	printf("input year : ");
	scanf("%d", &user_year);
	printf("input_month : ");
	scanf("%d", &user_month);
	user_month--;
	char user_string[10];
	char tmp[10];
	sprintf(user_string, "%d", user_year);
	strcat(user_string, "-");
	sprintf(tmp, "%02d", user_month);
	strcat(user_string, tmp);
	strcat(query, user_string);
	fgets(buffer, MAXLEN, fp);
	strcat(query, buffer);
	sprintf(user_string, "%d", user_year);
	strcat(user_string, "-");
	user_month++;
	sprintf(tmp, "%02d", user_month);
	strcat(user_string, tmp);
	strcat(query, user_string);
	fgets(buffer, MAXLEN, fp);
	strcat(query, buffer);
	fclose(fp);
	int state = 0;
	state = mysql_query(connection, query);
	if (state == 0)
	{
		sql_result = mysql_store_result(connection);
		printf("customer_id\tcustomer_address\tsum of charge\n");
		while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
		{
			printf("%s\t%s\t\t%s\n", sql_row[0], sql_row[1], sql_row[2]);
		}
		mysql_free_result(sql_result);
	}
}