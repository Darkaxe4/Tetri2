#include "Includes.hpp"

void JSONFileIO::write_json(const I_JSONSerializable& object, const path& file)
{
	auto full_path = _path / file;
	_stream.open(
		full_path,
		std::ios::out | std::ios::trunc
	);
	_stream << object.to_json();
	_stream.close();
}

json JSONFileIO::read_json(const path& file)
{
	auto full_path = _path / file;
	_stream.open(
		full_path,
		std::ios::in
	);
	auto data = json::parse(_stream);
	_stream.close();
	return data;
}
