#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include"stb_image.h"
#include"stb_image_write.h"
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<math.h>

#define THRESHOLD 0.4
int skinHash[256][256][256];
int nonSkinHash[256][256][256];
long double ratio[256][256][256];

char* totalFileNameArray[555]={"0000","0040","0080","0120","0160","0200","0240","0280","0320","0360","0400","0440","0480","0520","0001","0041","0081","0121","0161","0201","0241","0281","0321","0361","0401","0441","0481","0521","0002","0042","0082","0122","0162","0202","0242","0282","0322","0362","0402","0442","0482","0522","0003","0043","0083","0123","0163","0203","0243","0283","0323","0363","0403","0443","0483","0523","0004","0044","0084","0124","0164","0204","0244","0284","0324","0364","0404","0444","0484","0524","0005","0045","0085","0125","0165","0205","0245","0285","0325","0365","0405","0445","0485","0525","0006","0046","0086","0126","0166","0206","0246","0286","0326","0366","0406","0446","0486","0526","0007","0047","0087","0127","0167","0207","0247","0287","0327","0367","0407","0447","0487","0527","0008","0048","0088","0128","0168","0208","0248","0288","0328","0368","0408","0448","0488","0528","0009","0049","0089","0129","0169","0209","0249","0289","0329","0369","0409","0449","0489","0529","0010","0050","0090","0130","0170","0210","0250","0290","0330","0370","0410","0450","0490","0530","0011","0051","0091","0131","0171","0211","0251","0291","0331","0371","0411","0451","0491","0531","0012","0052","0092","0132","0172","0212","0252","0292","0332","0372","0412","0452","0492","0532","0013","0053","0093","0133","0173","0213","0253","0293","0333","0373","0413","0453","0493","0533","0014","0054","0094","0134","0174","0214","0254","0294","0334","0374","0414","0454","0494","0534","0015","0055","0095","0135","0175","0215","0255","0295","0335","0375","0415","0455","0495","0535","0016","0056","0096","0136","0176","0216","0256","0296","0336","0376","0416","0456","0496","0536","0017","0057","0097","0137","0177","0217","0257","0297","0337","0377","0417","0457","0497","0537","0018","0058","0098","0138","0178","0218","0258","0298","0338","0378","0418","0458","0498","0538","0019","0059","0099","0139","0179","0219","0259","0299","0339","0379","0419","0459","0499","0539","0020","0060","0100","0140","0180","0220","0260","0300","0340","0380","0420","0460","0500","0540","0021","0061","0101","0141","0181","0221","0261","0301","0341","0381","0421","0461","0501","0541","0022","0062","0102","0142","0182","0222","0262","0302","0342","0382","0422","0462","0502","0542","0023","0063","0103","0143","0183","0223","0263","0303","0343","0383","0423","0463","0503","0543","0024","0064","0104","0144","0184","0224","0264","0304","0344","0384","0424","0464","0504","0544","0025","0065","0105","0145","0185","0225","0265","0305","0345","0385","0425","0465","0505","0545","0026","0066","0106","0146","0186","0226","0266","0306","0346","0386","0426","0466","0506","0546","0027","0067","0107","0147","0187","0227","0267","0307","0347","0387","0427","0467","0507","0547","0028","0068","0108","0148","0188","0228","0268","0308","0348","0388","0428","0468","0508","0548","0029","0069","0109","0149","0189","0229","0269","0309","0349","0389","0429","0469","0509","0549","0030","0070","0110","0150","0190","0230","0270","0310","0350","0390","0430","0470","0510","0550","0031","0071","0111","0151","0191","0231","0271","0311","0351","0391","0431","0471","0511","0551","0032","0072","0112","0152","0192","0232","0272","0312","0352","0392","0432","0472","0512","0552","0033","0073","0113","0153","0193","0233","0273","0313","0353","0393","0433","0473","0513","0553","0034","0074","0114","0154","0194","0234","0274","0314","0354","0394","0434","0474","0514","0554","0035","0075","0115","0155","0195","0235","0275","0315","0355","0395","0435","0475","0515","0036","0076","0116","0156","0196","0236","0276","0316","0356","0396","0436","0476","0516","0037","0077","0117","0157","0197","0237","0277","0317","0357","0397","0437","0477","0517","0038","0078","0118","0158","0198","0238","0278","0318","0358","0398","0438","0478","0518","0039","0079","0119","0159","0199","0239","0279","0319","0359","0399","0439","0479","0519"};
int main()
{
    // initialize skinHash and nonSkinHash
    for(int i=0; i<256; i++)
    {
        for(int j=0; j<256; j++)
        {
            for(int k=0; k<256; k++)
            {
                skinHash[i][j][k]=0;
                nonSkinHash[i][j][k]=0;
            }
        }
    }

    clock_t startTime=clock();
    //read each file
    for(int i=0; i<555; i++)
    {
        // file name construction
        char maskPath[20];
        maskPath[0]='\0';
        strcat(maskPath,"ibtd/Mask/");
        strcat(maskPath,totalFileNameArray[i]);
        strcat(maskPath,".bmp");
        char orgPath[20];
        orgPath[0]='\0';
        strcat(orgPath,"ibtd/");
        strcat(orgPath,totalFileNameArray[i]);
        strcat(orgPath,".jpg");


        // load image data
        int hb,wb,channelb;
        int hj,wj,channelj;

        unsigned char* bmpData=stbi_load(maskPath,&hb,&wb,&channelb,STBI_rgb);
        if (!bmpData)
        {
            //puts("gh");
            fprintf(stderr, "Error loading the BMP image\n");
            return 1;
        }
        unsigned char* jpgData=stbi_load(orgPath,&hj,&wj,&channelj,STBI_rgb);
        if (!jpgData)
        {
            fprintf(stderr, "Error loading the JPG image\n");
            return 1;
        }

        // read from bmp ; frequency counting
        for(int a=0; a<hb; a++)
        {
            for(int b=0; b<wb; b++)
            {
                int idx=((a*wb)+b)*channelb;

                unsigned char red=bmpData[idx];
                unsigned char green=bmpData[idx+1];
                unsigned char blue=bmpData[idx+2];

                //printf("%d %d %d\n",red,green,blue);

                if(red>220 && green>220 && blue>220)
                {
                    red=jpgData[idx];
                    green=jpgData[idx+1];
                    blue=jpgData[idx+2];
                    //printf("%d %d %d\n",red,green,blue);
                    nonSkinHash[red][green][blue]++;
                }
                else
                    skinHash[red][green][blue]++;
            }
        }
        stbi_image_free(jpgData);
        stbi_image_free(bmpData);
        printf("image processed %d\n",i+1);
    }

    // total sum: skin and nonskin
    long skinSum=0,nonSkinSum=0;
    int cnt=0;
    for(int i=0; i<256; i++)
    {
        for(int j=0; j<256; j++)
        {
            for(int k=0; k<256; k++)
            {
                skinSum+=skinHash[i][j][k];
                nonSkinSum+= nonSkinHash[i][j][k];
            }
        }
    }


    printf("%ld %ld\n",skinSum,nonSkinSum);
    //return 0;

    // check 232, 190, 172

    // probability calculation
    long double skinProbability,nonSkinProbability;
    for(int i=0; i<256; i++)
    {
        for(int j=0; j<256; j++)
        {
            for(int k=0; k<256; k++)
            {
                skinProbability=((1.0L)*skinHash[i][j][k])/((1.0L)*skinSum);
                nonSkinProbability=((1.0L)*nonSkinHash[i][j][k])/((1.0L)*nonSkinSum);

                if(nonSkinProbability==0 && skinProbability==0)
                    {ratio[i][j][k]=0;}  // skin
                else if(nonSkinProbability==0 && skinProbability!=0)
                    {ratio[i][j][k]=1;}
                else
                    {ratio[i][j][k]=skinProbability/nonSkinProbability;}
                //printf("%.20lf\n",ratio[i][j][k]);
            }
        }
    }

    printf("training done\n");
    clock_t endTime=clock();
    double time=((double)(endTime-startTime)/CLOCKS_PER_SEC);
    printf("Training time %lf\n",time);

    // testing
    startTime=clock();
    const char* input="testing/pic25.jpg";
    const char* output="output/pic25_mask.bmp";
    int h,w,channel;

    unsigned char* jpgData1=stbi_load(input,&h,&w,&channel,STBI_rgb);
    if (!jpgData1)
    {
        fprintf(stderr, "Error loading the JPG image\n");
        return 1;
    }

    unsigned char* orgData=(unsigned char*)malloc(h*w*channel);
    if (!orgData)
    {
        fprintf(stderr, "Error allocating memory\n");
        stbi_image_free(orgData);
        return 1;
    }

    //
    for(int a=0; a<h; a++)
    {
        for(int b=0; b<w; b++)
        {
            int idx=((a*w)+b)*channel;

            unsigned char red=jpgData1[idx];
            unsigned char green=jpgData1[idx+1];
            unsigned char blue=jpgData1[idx+2];

            if(fabs(ratio[red][green][blue])<THRESHOLD)
            {
                orgData[idx]=255;
                orgData[idx+1]=255;
                orgData[idx+2]=255;
            }
            else
            {
                orgData[idx]=red;
                orgData[idx+1]=green;
                orgData[idx+2]=blue;
            }
        }
    }

    if(!stbi_write_bmp(output,h,w,channel,orgData))
    {
        fprintf(stderr, "Error writing the BMP image\n");
        free(orgData);
        stbi_image_free(jpgData1);
        return 1;
    }
    endTime=clock();
    time=((double)(endTime-startTime)/CLOCKS_PER_SEC);
    printf("testing time %lf\n",time);
    free(orgData);
    stbi_image_free(jpgData1);
}

