// EstimatorTestAP.cpp : 定義應用程式的進入點。
//

#include "stdafx.h"
#include "EstimatorTestAP.h"

#define PARAM_ESTIMATE_TEST

double g_dbArray[25] = {0.339927470128817, 0.357793108815364, 0.297765891078604, 0.0746975339990457, 0.109424978070786, 
						0.202862233341773, 0.827006228683624, 0.749767521711378, 0.0546709971545927, 0.581587358635332, 
						0.248601133605626, 0.586778370641617, 0.756673631396561, 0.530511970198909, 0.464334181842462, 
						0.624199424430928, 0.544749810872797, 0.370774230062180, 0.780105254458703, 0.0285104987758238, 
						0.468322389720054, 0.920222839102907, 0.573711913355992, 0.933439402379952, 0.327007668043390};
double g_dbTmpArr1[25];
double g_dbTmpArr2[25];

#ifdef PARAM_ESTIMATE_TEST
#include "ParamEstimator_Export.h"

//double	g_PH[10*5] = {0.537667139546100,	-1.34988694015652,	0.671497133608081,	0.888395631757642,	-0.102242446085491,
//					 1.83388501459509,	3.03492346633185,	-1.20748692268504,	-1.14707010696915,	-0.241447041607358,
//					-2.25884686100365,	0.725404224946106,	0.717238651328839,	-1.06887045816803,	0.319206739165502,
//					0.862173320368121,	-0.0630548731896562,	1.63023528916473,	-0.809498694424876,	0.312858596637428,
//					0.318765239858981,	0.714742903826096,	0.488893770311789,	-2.94428416199490,	-0.864879917324457,
//					-1.30768829630527,	-0.204966058299775,	1.03469300991786,	1.43838029281510,	-0.0300512961962686,
//					-0.433592022305684,	-0.124144348216312,	0.726885133383238,	0.325190539456198,	-0.164879019209038,
//					0.342624466538650,	1.48969760778547,	-0.303440924786016,	-0.754928319169703,	0.627707287528727,
//					3.57839693972576,	1.40903448980048,	0.293871467096658,	1.37029854009523,	1.09326566903948,
//					2.76943702988488,	1.41719241342961,	-0.787282803758638,	-1.71151641885370,	1.10927329761440};
//
//double g_PZ[10] = {2.03110213467170,
//				-1.43688536557928,
//				-2.54988763758495,
//				2.83956690548387,
//				-12.8934532042587,
//				8.52235361541256,
//				1.20547582943732,
//				2.90189888147641,
//				18.0000184239238,
//				3.05963039693985};
//
//double g_TP[5] = {1.0, 2.0, 3.0, 4.0, 5.0};	// true parameters

double	g_PH[20*5] = {0.387672857227010,1.12718635198620,	0.343792666564358,	-0.346292878031393,	-1.16256240410332,
					-0.782775420572307,	0.508790271452601,	1.05106471460986,	0.149849412946617,	0.130223527365399,
					-1.70242431307364,	-0.157880225490610,	-0.849052630824456,	0.0720276445630019,	-0.386369509952482,
					1.07711560629106,	0.845072541390849,	-0.152043242485238,	-0.613611436092609,	1.60065297773492,
					0.959586761686633,	0.639190912808983,	1.75056647060533,	-1.18209482753559,	0.591273376749004,
					-0.597041409719408,	0.739136547804016,	-0.0779942926905295,	-1.23084842772030,	0.491505313295882,
					-0.0719811615343259,0.00274368931479601,	-0.522082400789671,	0.389896262474429,	-0.647570852929537,
					0.480767738696790,	-1.85689659346880,	0.0629818308717170,	-0.477893718467461,	0.992770927195342,
					-0.260799673956048,	0.350106183006019,	-2.22275454690370,	0.605879114509728,	-0.790452750807849,
					0.159828019312723,	1.17377683150027,	0.898260198917533,	0.540679016153091,	1.22723883358347,
					1.87624202150408,	-0.448486546809128,	-0.569020370694908,	0.933670043027275,	-2.20138782545931,
					-0.00370271435426153,	-0.628679515874492,	-1.00564110769562,	0.625574317134019,	1.48751069681045,
					1.26311967946653,	-0.0974178684256868,	-0.488240472130906,	-0.293320195411723,	-0.703724126450506,
					0.904984108933125,	0.524311724551763,	-0.324495316856492,	0.0634401030481035,	-0.184618630003257,
					-0.749300285989674,	0.338867183774623,	-0.695323926049477,	0.292503944236043,	-0.143768351922331,
					1.26372444539365,	-0.418156490556024,	-2.00672858542293,	-0.0854239970978128,	0.311851530254381,
					-0.614774492162787,	1.52261319582141,	-0.805373674520454,	-1.00681184244266,	0.291563145008077,
					0.441163974588469,	-1.32444882132573,	-0.0720252112570499,	-0.470653637336070,	1.61750294741629,
					-0.0297946834036647,-1.39064173785740,	-0.977598275616295,	1.80721498146898,	-0.0822444970920521,
					-0.356444277257048,	2.48762432453425,	-0.577288126559509,	-0.432642701248300,	0.252172248624306,
					};

double g_PZ[20] = {-0.994146552487485,
					5.04994196768473,
					-6.05437468956733,
					8.50730434968539,
					1.26748490919021,
					-3.76708345909094,
					-0.910325693681669,
					-3.65999640592272,
					-2.88287528257142,
					13.3847742027202,
					-6.86296013862037,
					5.76066772910074,
					-5.12816550326088,
					-1.34811075660676,
					-0.315876870653230,
					-3.65944933297374,
					-4.76981775764919,
					-3.68303004347931,
					1.75343153385567,
					8.53781536200926,
					};

double g_TP[5] = {1.1, 3.3, 2.2, 5.5, 4.4};	// true parameters

double g_PX[5] = {0.0, 0.0, 0.0, 0.0, 0.0};	// estimates
double g_PV[20] = {1.0};

#else
#include "StateEstimatorExamples.h"

//Example	g_Demo = exPF;
Example	g_Demo = exFinalProject;
#endif

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	/* only for cholesky test
	double  H[]={2.67768733626021,2.58845139209795,1.19970135402198,1.76441224019023,1.95158423202149,
				 2.58845139209795,3.02911451715172,1.09969414336428,2.12406889861768,1.77684008321862,
				 1.19970135402198,1.09969414336428,0.737902717606714,0.677519640928402,1.06625768722290,
				 1.76441224019023,2.12406889861768,0.677519640928402,1.51810908890052,1.14422097241927,
				 1.95158423202149,1.77684008321862,1.06625768722290,1.14422097241927,1.74065586700877};
	fMatrix		MatH(5, 5, H); 
	char	Mess[512];
	wchar_t wLongMess[512];
	fMatrix		MatChol = Cholesky(MatH);
	Float*		elem = MatChol.Array();
	sprintf_s(Mess, 512, "Chol(H) = [%4.4f, %4.4f, %4.4f, %4.4f, %4.4f,\n\t %4.4f, %4.4f, %4.4f, %4.4f, %4.4f,\n\t %4.4f, %4.4f, %4.4f, %4.4f, %4.4f,\n\t %4.4f, %4.4f, %4.4f, %4.4f, %4.4f,\n\t %4.4f, %4.4f, %4.4f, %4.4f, %4.4f]\n", 
			elem[0], elem[1], elem[2], elem[3], elem[4],
			elem[5], elem[6], elem[7], elem[8], elem[9],
			elem[10], elem[11], elem[12], elem[13], elem[14],
			elem[15], elem[16], elem[17], elem[18], elem[19],
			elem[20], elem[21], elem[22], elem[23], elem[24]);
	MByteToWChar(Mess, wLongMess,sizeof(wLongMess)/sizeof(wLongMess[0]));
	::MessageBox(NULL,wLongMess,L"Chol(H)",MB_OK);
	*/

	fMatrix MatA(5,5,&g_dbArray[0]);
	fMatrix MatB(5,5,&g_dbArray[0]);
	fMatrix invMat = Inverse_GE(MatA);
	memcpy(g_dbTmpArr1,invMat.Array(), sizeof(double)*25);
	invMat = Inverse_QR(MatB);
	memcpy(g_dbTmpArr2,invMat.Array(), sizeof(double)*25);

#ifdef PARAM_ESTIMATE_TEST

	char	Message[8][256];
	char	LongMessage[512];
	wchar_t wLongMessage[512];

	fMatrix	MatH(20, 5, g_PH);
	fVector	VecZ(20, g_PZ);
	fVector	VecX(5, g_PX);
	//fVector	VecV(20, g_PV);
	//fMatrix MatVz = Diag(VecV);
	//LS_Param	Param = {&MatH, &VecZ, &MatVz};
	LS_Param	Param = {&MatH, &VecZ, NULL};

	fnSetParamEstiMethod(LS);
	fnSetMethodParameters(LS, &Param);
	fMatrix* MatErrVar = fnSolveOptParam(&VecX);
	fVector& VecVar  = Diag(*MatErrVar);
	
	memcpy(g_PX, VecX.Array(), sizeof(double)*5);
	memcpy(g_PV, VecVar.Array(), sizeof(double)*5);

	sprintf_s(&Message[0][0], 256, "Parameters: P_true = [%4.4f, %4.4f, %4.4f, %4.4f, %4.4f]',\n", 
			g_TP[0], g_TP[1], g_TP[2], g_TP[3], g_TP[4]);
	sprintf_s(&Message[1][0], 256, "LS Estimates: X_LS = [%4.4f, %4.4f, %4.4f, %4.4f, %4.4f]',\n", 
			g_PX[0], g_PX[1], g_PX[2], g_PX[3], g_PX[4]);
	sprintf_s(&Message[2][0], 256, "Error Var: V_LS = [%4.4f, %4.4f, %4.4f, %4.4f, %4.4f]',\n", 
			g_PV[0], g_PV[1], g_PV[2], g_PV[3], g_PV[4]);
	sprintf_s(	LongMessage, 512, "%s \n%s \n%s \nSimulation Finished", 
				&Message[0][0], 
				&Message[1][0], 
				&Message[2][0]);

	/*double H[6] = {1, -2, 1, 0, 1, 2};
	double Z[3] = {1, 2, 4};
	double X[2] = {0 ,0};
	fMatrix MatH1(3,2,H);
	fVector VecZ1(3,Z);
	fVector VecX1(2,X);
	Param.pMat_H = &MatH1;
	Param.pVec_Z = &VecZ1;
	Param.pMat_Vz = NULL;
	fnSetMethodParameters(LS, &Param);
	fnSolveOptParam(&VecX1);
	X[0] = VecX1(0);
	X[1]= VecX1(1);*/

	MByteToWChar(LongMessage, wLongMessage,sizeof(wLongMessage)/sizeof(wLongMessage[0]));
	::MessageBox(NULL,wLongMessage,L"Message",MB_OK);


	fVector&	VecV = VecZ - MatH * VecX;
	fMatrix		MatVv = Diag(Diag(Cov(VecV)));
	ML_Param	MLParam = {&MatH, &VecZ, &MatVv};

	fnSetParamEstiMethod(ML);
	fnSetMethodParameters(ML, &MLParam);
	MatErrVar = fnSolveOptParam(&VecX);
	fVector& MLVecVar  = Diag(*MatErrVar);

	memcpy(g_PX, VecX.Array(), sizeof(double)*5);
	memcpy(g_PV, MLVecVar.Array(), sizeof(double)*5);

	sprintf_s(&Message[0][0], 256, "Parameters: P_true = [%4.4f, %4.4f, %4.4f, %4.4f, %4.4f]',\n", 
			g_TP[0], g_TP[1], g_TP[2], g_TP[3], g_TP[4]);
	sprintf_s(&Message[1][0], 256, "ML Estimates: X_ML = [%4.4f, %4.4f, %4.4f, %4.4f, %4.4f]',\n", 
			g_PX[0], g_PX[1], g_PX[2], g_PX[3], g_PX[4]);
	sprintf_s(&Message[2][0], 256, "Error Var: V_ML = [%4.4f, %4.4f, %4.4f, %4.4f, %4.4f]',\n", 
			g_PV[0], g_PV[1], g_PV[2], g_PV[3], g_PV[4]);
	sprintf_s(	LongMessage, 512, "%s \n%s \n%s \nSimulation Finished", 
				&Message[0][0], 
				&Message[1][0], 
				&Message[2][0]);

	MByteToWChar(LongMessage, wLongMessage,sizeof(wLongMessage)/sizeof(wLongMessage[0]));
	::MessageBox(NULL,wLongMessage,L"Message",MB_OK);

#else
	if (g_Demo == exKF)
		Example_KalmanFilterDesign();
	else if (g_Demo == exIF)
		Example_InformationFilterDesign();
	else if (g_Demo == exEKF)
		Example_ExtendedKalmanFilterDesign();
	else if (g_Demo == exEIF)
		Example_ExtendedInformationFilterDesign();
	else if (g_Demo == exPF)
		Example_ParticleFilterDesign();
	else if (g_Demo == exFinalProject)
		Example_FinalProject();
	else
		Example_KalmanFilterDesign();
#endif

	return (int) TRUE;
}




