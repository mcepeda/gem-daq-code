#include <iomanip>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <cstdint>
#include <bitset>
#include <memory>
#include <map>

#include "gem/readout/GEMDataAMCformat.h"
#include "gem/datachecker/GEMDataChecker.h"
#include "GEMClusterization/GEMStrip.h"
#include "GEMClusterization/GEMStripCollection.h"


#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <array>

#include "TH2F.h"
#include "TCanvas.h"

#if defined(__CINT__) && !defined(__MAKECINT__)
#include "libEvent.so"
#else
#include "Event.h"
#include "CosmicStandEvent.h"
#endif

int main(int argc, char** argv)
{


        TH2F * hchamber = new TH2F("hchamber","",125,0,125,100,-50,50);
        hchamber->SetXTitle("Y [cm] (related to ieta)");
        hchamber->SetYTitle("X [cm] (related to phi)");
        TH2F * hlateral = new TH2F("hlateral","",125,0,125,70,0,70);
        hlateral->SetXTitle("Y [cm] (related to ieta)");
        hlateral->SetYTitle("Z [cm]");
        TH2F * hfrontal = new TH2F("hfrontal","",100,-50,50,70,0,70);
        hfrontal ->SetYTitle("Z [cm]");
        hfrontal ->SetXTitle("X [cm] (related to phi)");

        std::string slotfile_="dummy.csv";
        std::unique_ptr<gem::readout::GEMslotContents> slotInfo_ = std::unique_ptr<gem::readout::GEMslotContents> (new gem::readout::GEMslotContents(slotfile_));

        int event=0;
        int run=1;     
 
        CosmicStandEvent stand(run, event);

        for (int sc=0; sc<4; sc++){

        SuperChamber superChamber(sc);

        for (int ic=0; ic<2; ic++){

        for (int slot=0; slot<24;slot++){
                GEBdata *GEBdata_ = new GEBdata(0, 1, 24);
                for(int ivfat=0; ivfat<1; ivfat++){
                        uint8_t   b1010  = 0xa; 
                        uint16_t  BC     = 0;
                        uint8_t   b1100  = 0xc;
                        uint8_t   EC     = 0;
                        uint8_t   Flag   = 0;
                        uint8_t   b1110  = 0xe; 
                        uint16_t  ChipID = slotInfo_->GEBChipIdFromSlot(slot);;
                        uint16_t  CRC    = 0;//
                        uint64_t  lsData = 0xfffffffff;
                        uint64_t  msData = 0xfffffffff;
                        uint16_t checkedCRC = 0;
                        uint32_t ZSFlag24 = 0;
                        bool blockStatus = true;
                        VFATdata *VFATdata_ = new VFATdata(b1010, BC, b1100, EC, Flag, b1110, ChipID, lsData, msData, CRC, checkedCRC, slot, blockStatus);
                        GEBdata_->addVFATData(*VFATdata_);
                }


                Chamber chamber(0,ic,sc,*GEBdata_,slotfile_);
                chamber.Build();
                std::vector<SingleStrip> strips=chamber.strips();

                superChamber.addChamberData(chamber);

                for (int i=0; i<strips.size(); i++){
                        SingleStrip testStrip2=strips.at(i); 
                        hchamber->Fill(testStrip2.y(),testStrip2.x());
                        hlateral->Fill(testStrip2.y(),testStrip2.height());
                        hfrontal->Fill(testStrip2.x(),testStrip2.height());

                }

        }
        }
            stand.addSuperChamberData(superChamber);
        }


        TCanvas *c1= new TCanvas("c1");c1->Divide(3,1);
        c1->cd(1);
        hchamber->Draw("box");
        c1->cd(2);
        hlateral->Draw();
        c1->cd(3);
        hfrontal->Draw("box");
        c1->SaveAs("test.png");
}

