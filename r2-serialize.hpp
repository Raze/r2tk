/* HEADER
 *
 * File: r2-serialize.hpp
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
 * Depends on:
 *	+ r2-data-types.hpp
 *	+ r2::Exception::Overflow
 *	+ r2::Exception::Underflow
 * Updates:
 *
 */
#ifndef R2_SERIALIZE_HPP
#define R2_SERIALIZE_HPP

#include <string>
#include "r2-data-types.hpp"

namespace r2 {
	class Serializer;
	class Serializable;
	class SerialSizer;
	class SerialSaver;
	class SerialLoader;



	class Serializable {
	public:
		virtual void Serialize(Serializer& p_serializer) = 0;
	};



	class Serializer {
	public:
		virtual void IO(SInt8& p_data) = 0;
		virtual void IO(SInt16& p_data) = 0;
		virtual void IO(SInt32& p_data) = 0;
		virtual void IO(SInt64& p_data) = 0;
	
		virtual void IO(UInt8& p_data) = 0;
		virtual void IO(UInt16& p_data) = 0;
		virtual void IO(UInt32& p_data) = 0;
		virtual void IO(UInt64& p_data) = 0;
	
		virtual void IO(bool& p_data) = 0;
	
		virtual void IO(float& p_data) = 0;
		virtual void IO(double& p_data) = 0;
	
		virtual void IO(std::string& p_data) = 0;
	};






	class SerialSizer : public Serializer {
	public:
		SerialSizer() : m_size(0) {}
		
		
		virtual void IO(SInt8& p_data);
		virtual void IO(SInt16& p_data);
		virtual void IO(SInt32& p_data);
		virtual void IO(SInt64& p_data);
		
		virtual void IO(UInt8& p_data);
		virtual void IO(UInt16& p_data);
		virtual void IO(UInt32& p_data);
		virtual void IO(UInt64& p_data);
		
		virtual void IO(bool& p_data);
		
		virtual void IO(float& p_data);
		virtual void IO(double& p_data);
		
		virtual void IO(std::string& p_data);
		
		
		inline unsigned long GetSize() const { return m_size; }
	protected:
		unsigned long m_size;
	};






	class SerialSaver : public Serializer {
	public:
		SerialSaver(Byte* p_buffer, unsigned long p_buffer_size);
		
		
		virtual void IO(SInt8& p_data);
		virtual void IO(SInt16& p_data);
		virtual void IO(SInt32& p_data);
		virtual void IO(SInt64& p_data);
		
		virtual void IO(UInt8& p_data);
		virtual void IO(UInt16& p_data);
		virtual void IO(UInt32& p_data);
		virtual void IO(UInt64& p_data);
		
		virtual void IO(bool& p_data);
		
		virtual void IO(float& p_data);
		virtual void IO(double& p_data);
		
		virtual void IO(std::string& p_data);
		
		
		unsigned long GetNumberOfBytesRemaining() const { return m_buffer_size - m_bytes_saved; }
		unsigned long GetNumberOfSavedBytes() const { return m_bytes_saved; }
	protected:
		void Write(const void* p_data, int p_size);
	private:
		Byte* m_buffer;
		unsigned long m_buffer_size;
		
		unsigned long m_bytes_saved;
	};







	class SerialLoader : public Serializer {
	public:
		SerialLoader(Byte* p_buffer, unsigned long p_buffer_size);
		
		
		virtual void IO(SInt8& p_data);
		virtual void IO(SInt16& p_data);
		virtual void IO(SInt32& p_data);
		virtual void IO(SInt64& p_data);
		
		virtual void IO(UInt8& p_data);
		virtual void IO(UInt16& p_data);
		virtual void IO(UInt32& p_data);
		virtual void IO(UInt64& p_data);
		
		virtual void IO(bool& p_data);
		
		virtual void IO(float& p_data);
		virtual void IO(double& p_data);
		
		virtual void IO(std::string& p_data);
		
		
		unsigned long GetNumberOfBytesRemaining() const { return m_buffer_size - m_bytes_loaded; }
		unsigned long GetNumberOfLoadedBytes() const { return m_bytes_loaded; }
	protected:
		void Load(void* p_target, int p_size);
	private:
		Byte* m_buffer;
		unsigned long m_buffer_size;
		
		unsigned long m_bytes_loaded;
	};
}

#endif	/* R2_SERIALIZE_HPP */
