/* SOURCE
 *
 * File: r2-serialize.cpp
 * Created by: Lars Woxberg (Rarosu)
 * Created on: August 15 2011, 16:30
 *
 * License:
 *   Copyright (C) 2011 Lars Woxberg
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Lesser General Public License for more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>;.
 *
 * Comments:
 *
 * Updates:
 *
 */
#include "r2-serialize.hpp"
#include "r2-exception.hpp"
#include <cstring>

namespace r2 {
	
	void SerialSizer::IO(SInt8& p_data) {
		m_size += 1;
	}
	
	void SerialSizer::IO(SInt16& p_data) {
		m_size += 2;
	}
	
	void SerialSizer::IO(SInt32& p_data) {
		m_size += 4;
	}
	
	void SerialSizer::IO(SInt64& p_data) {
		m_size += 8;
	}
	
	
	
	
	void SerialSizer::IO(UInt8& p_data) {
		m_size += 1;
	}
	
	void SerialSizer::IO(UInt16& p_data) {
		m_size += 2;
	}
	
	void SerialSizer::IO(UInt32& p_data) {
		m_size += 4;
	}
	
	void SerialSizer::IO(UInt64& p_data) {
		m_size += 8;
	}
	
	
	
	
	void SerialSizer::IO(bool& p_data) {
		m_size += 1;
	}
	
	
	
	
	void SerialSizer::IO(float& p_data) {
		m_size += 4;
	}
	
	void SerialSizer::IO(double& p_data) {
		m_size += 8;
	}
	
	
	void SerialSizer::IO(std::string& p_data) {
		UInt64 length = static_cast<UInt64>( p_data.length() );
		IO( length );
		m_size += length;
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	SerialSaver::SerialSaver(Byte* p_buffer, unsigned long p_buffer_size) :
		m_buffer(p_buffer),
		m_buffer_size(p_buffer_size),
		m_bytes_saved(0) {}
	
	
	void SerialSaver::Write(const void* p_data, int p_size) {
		if (m_bytes_saved + p_size > m_buffer_size) {
			throw r2ExceptionOverflowM("Serial Saver read in too much data - buffer would've been overflowed");
		}
		
		memcpy(m_buffer + m_bytes_saved, p_data, p_size);
		m_bytes_saved += p_size;
	}
	
	
	
	void SerialSaver::IO(SInt8& p_data) {
		Write(&p_data, 1);
	}
	
	void SerialSaver::IO(SInt16& p_data) {
		Write(&p_data, 2);
	}
	
	void SerialSaver::IO(SInt32& p_data) {
		Write(&p_data, 4);
	}
	
	void SerialSaver::IO(SInt64& p_data) {
		Write(&p_data, 8);
	}
	
	
	
	
	void SerialSaver::IO(UInt8& p_data) {
		Write(&p_data, 1);
	}
	
	void SerialSaver::IO(UInt16& p_data) {
		Write(&p_data, 2);
	}
	
	void SerialSaver::IO(UInt32& p_data) {
		Write(&p_data, 4);
	}
	
	void SerialSaver::IO(UInt64& p_data) {
		Write(&p_data, 8);
	}
	
	
	
	
	void SerialSaver::IO(bool& p_data) {
		Byte b = p_data ? 1 : 0;
		Write(&b, 1);
	}
	
	
	
	
	void SerialSaver::IO(float& p_data) {
		Write(&p_data, 4);
	}
	
	void SerialSaver::IO(double& p_data) {
		Write(&p_data, 8);
	}
	
	
	void SerialSaver::IO(std::string& p_data) {
		// first, write an integer holding the length of the string
		UInt64 length = static_cast<UInt64>( p_data.length() );
		IO( length );
		
		// second, write the string, but without the null-terminator (i.e. p_data.data())
		Write(p_data.data(), length);
	}
	
	
	
	
	
	
	
	
	
	
	
	
	SerialLoader::SerialLoader(Byte* p_buffer, unsigned long p_buffer_size) :
		m_buffer(p_buffer),
		m_buffer_size(p_buffer_size),
		m_bytes_loaded(0) {}
	
	
	void SerialLoader::Load(void* p_target, int p_size) {
		if (m_bytes_loaded + p_size > m_buffer_size) {
			throw r2ExceptionUnderflowM("Serial Loader has loaded too much data - buffer would've been underflowed");
		}
		
		memcpy(p_target, m_buffer + m_bytes_loaded, p_size);
		m_bytes_loaded += p_size;
	}
	
	
	void SerialLoader::IO(SInt8& p_data) {
		Load(&p_data, 1);
	}
	
	void SerialLoader::IO(SInt16& p_data) {
		Load(&p_data, 2);
	}
	
	void SerialLoader::IO(SInt32& p_data) {
		Load(&p_data, 4);
	}
	
	void SerialLoader::IO(SInt64& p_data) {
		Load(&p_data, 8);
	}
	
	
	void SerialLoader::IO(UInt8& p_data) {
		Load(&p_data, 1);
	}
	
	void SerialLoader::IO(UInt16& p_data) {
		Load(&p_data, 2);
	}
	
	void SerialLoader::IO(UInt32& p_data) {
		Load(&p_data, 4);
	}
	
	void SerialLoader::IO(UInt64& p_data) {
		Load(&p_data, 8);
	}
	
	
	void SerialLoader::IO(bool& p_data) {
		Byte b;
		Load(&b, 1);
		
		p_data = (b == 0) ? false : true;
	}
	
	
	void SerialLoader::IO(float& p_data) {
		Load(&p_data, 4);
	}
	
	void SerialLoader::IO(double& p_data) {
		Load(&p_data, 8);
	}
	
	
	void SerialLoader::IO(std::string& p_data) {
		UInt64 length;
		IO(length);
		
		char* string_buffer = new char[length + 1];
		try {
			Load(string_buffer, length);
			string_buffer[length] = '\0';
		
			p_data.resize(length + 1);
			p_data.assign(string_buffer, length + 1);
		} catch (...) {
			delete [] string_buffer;
			throw;
		}
		
		delete [] string_buffer;
	}
	
}