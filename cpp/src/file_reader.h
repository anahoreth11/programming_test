#pragma once

#include "data_types.h"

#include <string>
#include <fstream>
#include <istream>
#include <iostream>
#include <optional>

class Reader {
public:
	virtual std::optional<Row> ReadRow() {
		return std::nullopt;
	}

	virtual ~Reader() {}
};

class StreamReader : public Reader {
public:
	StreamReader(std::istream& stream) : _stream(stream) {}
	std::optional<Row> ReadRow() override;
	~StreamReader() {}

public:
	std::istream& _stream;
};
