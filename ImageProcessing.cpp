#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

int main()
{
    ifstream imagefile("image.ppm",ios::binary);

    if(!imagefile)
    {
        cerr<<" Error : Couldn't open the image file. "<<endl;
        return 1;
    }

    string magicNum;
    int width,height,maxcolor_val;
    imagefile>>magicNum>>width>>height>>maxcolor_val;

    if(magicNum != "P6")
    {
        cerr<<" Error : This Program only supports binary PPM images(P6 Format) "<<endl;
        return 1;
    }
    imagefile.ignore(1);
    vector<char> imagedata(width*height*3);
    imagefile.read(imagedata.data(),imagedata.size());

    imagefile.close();

    for(char& pixel : imagedata)
    {
        pixel = maxcolor_val - pixel;
    }
    ofstream outputfile("output.ppm",ios::binary);

    if(!outputfile)
    {
        cerr<<" Error : Couldn't create the output image file."<<endl;
        return 1;
    }
    outputfile <<"P6"<<endl;
    outputfile<<width<<" "<<height<<endl;
    outputfile<<maxcolor_val<<endl;

    outputfile.write(imagedata.data(),imagedata.size());

    outputfile.close();

    cout<<" Image processing Complete.Saved as output.ppm "<<endl;
    return 0;
}

