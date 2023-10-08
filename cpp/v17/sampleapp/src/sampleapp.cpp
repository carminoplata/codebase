#include "sampleapp.hpp"

#include <iostream>

SampleApp::SampleApp(const string& text)
    : text{text}
{
}

SampleApp::SampleApp(const SampleApp&& other)
{
    this->text = std::move(other.text);
}
    
SampleApp& SampleApp::operator=(const SampleApp&& other)
{
    this->text = std::move(other.text);
    return *this;
}

string SampleApp::getText() const
{
    return text;
}

void SampleApp::print(ostream& os)
{
    os << text << endl;
}