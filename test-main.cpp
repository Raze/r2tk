

#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include "r2-exception.hpp"
#include "r2-assert.hpp"
#include "r2-math.hpp"
#include "r2-argument-parser.hpp"
#include "r2-data-types.hpp"
#include "r2-serialize.hpp"





class HighscoreList : public r2::Serializable {
public:
	enum Difficulty { Easy, Normal, Hard };

	void AddEntry(const std::string& p_name, Difficulty p_difficulty, int p_score) {
		Entry entry;
		entry.m_name = p_name;
		entry.m_difficulty = p_difficulty;
		entry.m_score = p_score;
		
		m_entries.push_back(entry);
		std::sort(m_entries.begin(), m_entries.end());
	}

	void Print() {
		for (int i = 0; i < m_entries.size(); ++i) {
			std::cout << m_entries[i].m_name << " ";
			
			switch (m_entries[i].m_difficulty) {
				case Easy: std::cout << "Easy" << " "; break;
				case Normal: std::cout << "Normal" << " "; break;
				case Hard: std::cout << "Hard" << " "; break;
			}
			
			std::cout << m_entries[i].m_score << std::endl;
		}
	}

	void Save(const std::string& p_file_name) {
		r2::SerialSizer sizer;
		
		Serialize(sizer);
		
		r2::Byte* buffer = new r2::Byte[sizer.GetSize()];
		try {
			r2::SerialSaver saver(buffer, sizer.GetSize());
		
			Serialize(saver);
		
			FILE* file;
			file = fopen(p_file_name.c_str(), "w+b");
			if (file) {
				fwrite(buffer, 1, sizer.GetSize(), file); 
				fclose(file);
			} else {
				throw r2ExceptionIOM(std::string("Could not create/open file: ") + p_file_name);
			}
		} catch (...) {
			delete [] buffer;
			throw;
		}
		
		delete [] buffer;
	}
	
	void Load(const std::string& p_file_name) {
		FILE* file;
		file = fopen(p_file_name.c_str(), "rb");
		
		if (file) {
			unsigned long size;
			fseek(file, 0, SEEK_END);
			size = ftell(file);
			fseek(file, 0, SEEK_SET);
			
			r2::Byte* buffer = new r2::Byte[size];
			try {
				fread(buffer, 1, size, file);
				
				r2::SerialLoader loader(buffer, size);
				
				Serialize(loader);
			} catch (...) {
				delete [] buffer;
				throw;
			}
			delete [] buffer;
			
			fclose(file);
		} else {
			throw r2ExceptionIOM(std::string("Could not open file: ") + p_file_name);
		}
		
		
	}
	
	virtual void Serialize(r2::Serializer& p_serializer) {
		int size = m_entries.size();
		p_serializer.IO(size);
		m_entries.resize(size);
		
		for (int i = 0; i < size; ++i) {
			m_entries[i].Serialize(p_serializer);
		}
	}
private:
	
	class Entry : public r2::Serializable {
	public:
		Entry() : m_difficulty(Normal), m_score(0) {}
		Entry(std::string p_name, Difficulty p_difficulty, int p_score) : m_name(p_name), m_difficulty(p_difficulty), m_score(p_score) {}
		
		virtual void Serialize(r2::Serializer& p_serializer) {
			r2::UInt16 difficulty = m_difficulty;
			
			p_serializer.IO(m_name);
			p_serializer.IO(difficulty);
			p_serializer.IO(m_score);
			
			m_difficulty = static_cast<Difficulty>(difficulty);
		}
		
		bool operator<(const Entry& p_rhs) const {
			return m_score < p_rhs.m_score;
		}
		
		std::string m_name;
		Difficulty m_difficulty;
		int m_score;
	};
	
	std::vector<Entry> m_entries;
};








int main(int p_argc, char* p_argv[])
{
	try {
		throw r2ExceptionRuntimeM("Error");
	} catch (std::exception& p_exception) {
		std::cout << "Exception Test Passed" << std::endl;
		try {
			r2AssertM(false, "Error");
		} catch (std::exception& p_exception) {
			std::cout << "Assertion Test Passed" << std::endl;
		}
	}
	
	std::cout << r2::Math::K_PI << std::endl;
	r2::Math::FloatCompare(0.0f, 0.0f);
	
	std::cout << "Math Test Passed" << std::endl;
	
	
	std::cout << "sizeof(r2::Byte): " << sizeof(r2::Byte) << std::endl;
	
	std::cout << "sizeof(r2::SInt8): " << sizeof(r2::SInt8) << std::endl;
	std::cout << "sizeof(r2::SInt16): " << sizeof(r2::SInt16) << std::endl;
	std::cout << "sizeof(r2::SInt32): " << sizeof(r2::SInt32) << std::endl;
	std::cout << "sizeof(r2::SInt64): " << sizeof(r2::SInt64) << std::endl;
	
	std::cout << "sizeof(r2::UInt8): " << sizeof(r2::UInt8) << std::endl;
	std::cout << "sizeof(r2::UInt16): " << sizeof(r2::UInt16) << std::endl;
	std::cout << "sizeof(r2::UInt32): " << sizeof(r2::UInt32) << std::endl;
	std::cout << "sizeof(r2::UInt64): " << sizeof(r2::UInt64) << std::endl;

	union {
		r2::UInt64 i;
		r2::Byte c[8];
	} a = { 0x0102030405060708 };
	
	r2::SwapEndian(a.i);
	r2AssertM(a.c[0] == 0x08 && a.c[1] == 0x07 && a.c[2] == 0x06 && a.c[3] == 0x05 && a.c[4] == 0x04 && a.c[5] == 0x03 && a.c[6] == 0x02 && a.c[7] == 0x01, "64-bit endian swap failed");

	std::cout << "64-bit Endian Swap Test Succeeded" << std::endl;
	
	
	HighscoreList list;
	list.AddEntry("Rarosu", HighscoreList::Easy, 100);
	list.AddEntry("Raze", HighscoreList::Easy, 120);
	list.AddEntry("Rarosu", HighscoreList::Normal, 435);
	list.AddEntry("Raze", HighscoreList::Normal, 435);
	list.AddEntry("Rogan", HighscoreList::Hard, 695);
	list.AddEntry("Billy The Paperboy", HighscoreList::Hard, 780);
	list.Save("highscore.dat");
	//list.Print();
	
	HighscoreList loaded_list;
	loaded_list.Load("highscore.dat");
	loaded_list.Print();

	return 0;
}