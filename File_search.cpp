#include<iostream>
#include<filesystem>
#include<string>
#include<vector>
using std::vector;
using std::string;
using path = std::filesystem::path;
namespace fs = std::filesystem;
using std::cout;
using std::endl;
using std::cin;

enum Filetype{video,image,document,audio,other};

Filetype sort(const string& Filename);
string DeterminePath();

string search(const string& Filename, const string& first, const string& second, const string& third, const string& fourth,const string& fifth,const path& Pt);
string DeepSearch(const string& FileName,const path& Pt);

int main()
{
	bool search_again = true; 


	/*Vars for storing plausible search paths*/
	string Documents = "\\Documents"; 
	string Downloads = "\\Downloads";
	string Audio = "\\Music";
	string Picture = "\\Pictures";
	string Video = "\\Videos";
	string Filename, Res;


	/*Get search path i.e C:/Users/user */
	string p = DeterminePath();
	path Pt(p);
	while (search_again) {

		cout << "Enter name and format of file: (e.g fish.mp3)\n";
		cin.clear();
		std::getline(cin, Filename);
		Filetype f = sort(Filename);
		switch (f)
		{
			case video:
			{

				Res = search(Filename, Video, Downloads, Picture, Audio, Documents, Pt);
				break;
			}
			case audio:
			{
				Res = search(Filename, Audio, Downloads, Video, Picture, Documents, Pt);
				break;
			}
			case image:
			{
				Res = search(Filename, Picture, Downloads, Documents, Video, Audio, Pt);
				break;
			}
			default:
			{
				Res = DeepSearch(Filename, Pt);
				break;
			}
		}

		if (Res == "")
		{
			cout << "File not found\n" << "Enter yes to search again or any key to cancel : \n";
			string a;
			getline(cin, a);
			search_again = a == "yes" ? true : false;
			cin.clear();
		}
		else
		{
			cout << "Your File: " << Filename << " Was found at Path: " << Res << "\n";
			cout << "Enter yes to search again or any key to cancel: \n";
			string a;
			getline(cin, a);
			search_again = a == "yes" ? true : false;
			cin.clear();
		}
	}
	return 0;
}

Filetype sort(const string& Filename)
{
	string FormatType;
	for (size_t i = (size_t)Filename.size(); i > 0; i--)
	{
		if (Filename[i] == '.')
		{
			FormatType = Filename.substr(i+1, Filename.size() - i);
		}
	}

	vector<string>formatList{ 
		//Video files 0 - 5
		"mp4","mov","wmv","mkv","avi","avchd",
		//audio files 6 - 12
		"mp3","aac","ogg","flac","wav","aiff","alac",
		//image file 13 - 18
		"png","jpg","jpeg","tiff","gif","raw"
		//Document file 19 - 23
		,"pdf","txt","csv","docx","xlsx"
	};

	for (size_t i = 0; i < formatList.size(); i++)
	{
		if (FormatType == formatList[i])
		{
			if (i <= 5)
			{
				Filetype d = video;
				return d;
			}

			else if (i > 5 && i <= 12)
			{
				Filetype d = audio;
				return d;
			}
			else if (i > 12 && i <= 18)
			{
				Filetype d = image;
				return d;
			}
			else if (i > 18 && i <= 23)
			{
				Filetype d = document;
				return d;
			}
		}
		
	}
	cout << "WARNING: Unsupported file format/format does not exist. Will continue to deep search." << endl;
	Filetype d = other;
	return d;

}

string DeepSearch(const string& FileName, const path& Pt)
{
	cout << "DEEP SEARCHING...\n";
	for (const auto Entry : std::filesystem::recursive_directory_iterator(Pt))
	{
		if (FileName == Entry.path().filename())
		{
			return Entry.path().string();
		}

	}
	cout << "File not found" << endl;
	string ret = "";
	return ret;
}

string search(const string& Filename, const string& first, const string& second, const string& third, const string& fourth, const string& fifth, const path& Pt)
{
	cout << "SEARCHING...\n";
	path NewPath;
	string NewP = Pt.string() + first;
	NewPath.assign(NewP);
	for (auto const& Directory : fs::recursive_directory_iterator{ NewPath })
	{
		if (Filename == Directory.path().filename())
		{
			return Directory.path().string();
		}
	}

	NewP = Pt.string() + second;
	NewPath.assign(NewP);
	for (auto const& Directory : fs::recursive_directory_iterator{ NewPath })
	{
		if (Filename == Directory.path().filename())
		{
			return Directory.path().string();
		}
	}

	NewP = Pt.string() + third;
	NewPath.assign(NewP);
	for (auto const& Directory : fs::recursive_directory_iterator{ NewPath })
	{
		if (Filename == Directory.path().filename())
		{
			return Directory.path().string();
		}
	}

	NewP = Pt.string() + fourth;
	NewPath.assign(NewP);
	for (auto const& Directory : fs::recursive_directory_iterator{ NewPath })
	{
		if (Filename == Directory.path().filename())
		{
			return Directory.path().string();
		}
	}

	NewP = Pt.string() + fifth;
	NewPath.assign(NewP);
	for (auto const& Directory : fs::recursive_directory_iterator{ NewPath })
	{
		if (Filename == Directory.path().filename())
		{
			return Directory.path().string();
		}
	}
	NewP = "";
	return NewP;
}

string DeterminePath()
{
	string ret ;
	string p = std::filesystem::current_path().string();
	for (size_t i = 0; i < p.size(); ++i)
	{
		if (p[i] == 'U' && p[i + 1] == 's' && p[i + 2] == 'e')
		{
			i += 6;
			while (p[i] != '\\') i++;
			ret = p.substr(0,i);
			
			return ret;
		}
	}
	ret = "could not initialize path";
	return ret;
}


