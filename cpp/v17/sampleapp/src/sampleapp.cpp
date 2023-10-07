#include "sampleapp.hpp"

#include <iostream>

SampleApp::SampleApp(const string& text)
    : text{text}
{
}

SampleApp::SampleApp(const SampleApp&& other)
{
    this->text = std::move(text);
}
    
SampleApp& SampleApp::operator=(const SampleApp&& other)
{
    this->text = std::move(text);
    return *this;
}

string SampleApp::getText() const
{
    return text;
}

void SampleApp::print()
{
    cout << text << endl;
}