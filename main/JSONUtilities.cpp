#include "Includes.hpp"

void JSONWriter::write_json(I_JSONSerializable& object, const path& file)
{
	_stream.open(
		_path += file,
		std::ios::out | std::ios::trunc
	);
	_stream << object.to_json();
	_stream.close();
}

const json& JSONWriter::read_json(const path& file)
{
	_stream.open(
		_path += file,
		std::ios::in | std::ios::trunc
	);
	auto data = json::parse(_stream);
	_stream.close();
	return data;
}
