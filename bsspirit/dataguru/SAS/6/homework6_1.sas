LIBNAME homework "D:\dataguru\SAS\6";
/*DATA homework.ch1;*/
/* 	RETAIN _seed_ 0;*/
/*	RETAIN _size_ 100;*/
/*	DO _i_ =1 TO _size_;*/
/*		IF _i_ LE _size_/2 THEN glass='�װ�' ;*/
/*		ELSE glass='�Ұ�';*/
/*		x1 = round(ranuni(_seed_)*100);*/
/*		x2 = round(ranuni(_seed_)*100);*/
/*		x3 = round(ranuni(_seed_)*100);*/
/*		ave = round(MEAN(OF x1-x3));*/
/*		OUTPUT;*/
/*    END;*/
/*	DROP _seed_ _size_;*/
/* RUN;*/
/* PROC PRINT;*/
/* RUN;*/

/*��һ��*/
/*PROC FORMAT;*/
/*VALUE vfmt LOW-<60='������'*/
/*		   60-<85='����'*/
/*		   85-HIGH='��';*/
/*PROC FREQ DATA=homework.ch1;*/
/*	FORMAT ave vfmt.;*/
/*	TABLEs ave;*/
/*RUN;*/

/*�ڶ���*/
/*PROC FORMAT;*/
/*VALUE vfmt LOW-<60='������'*/
/*		   60-<85='����'*/
/*		   85-HIGH='��';*/
/*DATA homework.ch2;*/
/*	set homework.ch1;*/
/*	FORMAT x1 x2 x3 vfmt.;*/
/*	DROP ave;*/
/*RUN;*/
/*PROC TABULATE;*/
/*	CLASS  glass x1 x2 x3;*/
/*	TABLE glass * (N*F=6.0 PCTN<x1 x2 x3>*F=6.2),x1 x2 x3 ;*/
/*	LABEL glass='�༶' x1='����' x2='��ѧ' x3='Ӣ��';*/
/*	KEYLABEL N='����' PCTN='�ٷֱ�';*/
/*RUN;*/

/*������*/
PROC FORMAT;
VALUE vfmt LOW-<60='������'
		   60-<85='����'
		   85-HIGH='��';
DATA homework.ch3;
	set homework.ch1;
	FORMAT ave vfmt.;
	DROP x1 x2 x3 glass;
RUN;
PROC PRINT DATA=homework.ch3;
RUN;
OPTION PS=30;
PROC GCHART DATA=homework.ch3;
	PIE ave / DISCRETE;
RUN;






