// This assumes a long chamber   (LC)
double LC_LongEdgeB_EtaPartition[8]={44.5858, 41.1313, 37.6769, 34.808, 31.9391, 29.541, 27.1428, 25.1263};
double LC_LongEdgeH_EtaPartition[8]={120.9,101.445,81.99,65.833,49.76,36.17,22.664,11.307};
double LC_ShortEdgeH_EtaPartition[8]={101.495,82.04,65.883,49.726,36.22,22.714,11.357,0};
double LC_ShortEdgeB_EtaPartition[8]={41.1402, 37.6857, 34.8169, 31.948, 29.5499, 27.1517,25.1351, 23.1186};
double LC_angle=10.15*TMath::Pi()/180;
int    Total_Channels=128*3;
double LC_FullR = (LC_LongEdgeB_EtaPartition[0]/2) /tan(LC_angle/2);
double LC_SmallR = LC_ShortEdgeB_EtaPartition[7]/2 /tan(LC_angle/2);
double Stand_distancebetweenchambersinoneSC=0.384;
double Stand_distancebetweenSC=20;


// ALL NAMES TO BE REVISED!!! TO MAKE THEM FOLLOW TDR
