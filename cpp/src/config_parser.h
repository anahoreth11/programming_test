#pragma once

#include <optional>
#include <string>

#include "data_types.h"

std::optional<Configs> get_configs_from_file(const std::string& config_file_name);

std::optional<Configs> get_configs_from_line(const std::string& config_line);
