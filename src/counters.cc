// Copyright (c) 2017 Carlo Contavalli (ccontavalli@gmail.com).
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//    1. Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
//    2. Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in the
//    documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY Carlo Contavalli ''AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
// EVENT SHALL Carlo Contavalli OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// The views and conclusions contained in the software and documentation are
// those of the authors and should not be interpreted as representing official
// policies, either expressed or implied, of Carlo Contavalli.

#include "counters.h"
#include "json-helpers.h"

Register& GlobalRegister() {
  static auto* counters = new Register();
  return *counters;
}

std::ostream* NullStream() {
  static auto* nullstream = new std::ofstream;
  return nullstream;
}

Counter& MakeCounter(const char* path, const char* description) {
  return GlobalRegister().MakeCounter(path, description);
}

Counter& Register::MakeCounter(const char* path, const char* description) {
  auto result = counters_.emplace(
      std::pair<std::string, Counter>(path, {path, description, NullStream()}));
  return result.first->second;
}

int Register::Capture(const std::string& match, std::ostream* stream) {
  std::regex regex(match);
  int matched = 0;
  for (auto& it : counters_) {
    const auto& name = it.first;
    auto& counter = it.second;

    if (!std::regex_search(name, regex)) continue;

    matched++;
    if (stream != nullptr) {
      (*stream) << "COUNTER - enabling capture of '" << name << "'"
                << std::endl;
      counter.Capture(stream);
    } else {
      counter.Capture(NullStream());
    }
  }
  return matched;
}

bool Register::OutputJson(const std::string& path) const {
  if (!MakeDirs(path, 0777)) {
    return false;
  }
  std::ofstream myfile;
  myfile.open(path);

  json::OStreamWrapper osw(myfile);
  json::PrettyWriter<json::OStreamWrapper> writer(osw);

  auto values = MakeJsonArray(&writer);
  for (const auto& it : counters_) {
    const auto& name = it.first;
    const auto& value = it.second;
    auto obj = MakeJsonObject(&writer);

    WriteJsonKeyValue(&writer, "metric", name);
    WriteJsonKeyValue(&writer, "value", value.Value());
  }
  return true;
}

DebugStream Counter::Add(SourceRange range) {
  return Add(range.getBegin(), range.getEnd());
}

DebugStream Counter::Add(SourceLocation begin, SourceLocation end) {
  return Add();
}

void Counter::Capture(std::ostream* capture) { capture_ = capture; }

DebugStream Counter::Add() {
  counter_++;

  *capture_ << "COUNTER - " << name_ << ": ";
  return DebugStream(*capture_);
}
