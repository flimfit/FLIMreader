#include "FLIMReader.h"
#include "PicoquantTTRReader.h"
#include "TextReader.h"

FLIMReader* FLIMReader::createReader(std::string& filename)
{
   std::string extension = determineExtension(filename);

   if (extension == "txt" || extension == "csv")
      return new TextReader(filename);
   else if (extension == "pt3")
      return new PicoquantTTTRReader(filename);

   throw std::runtime_error("Unrecognised file format");
}

FLIMReader::FLIMReader(const std::string& filename_)
{
   filename = filename_;
   extension = determineExtension(filename);

   n_x = 1;
   n_y = 1;
   temporal_resolution_ = 1;
}

std::string FLIMReader::determineExtension(std::string& filename)
{
   size_t last_dot, pos = 0;
   while ((pos = filename.find('.', pos + 1)) != std::string::npos)
      last_dot = pos + 1;
   return filename.substr(last_dot);
}

std::vector<int> FLIMReader::validateChannels(std::vector<int> channels, int& n_chan_stride)
{
   int n_chan = numChannels();

   std::vector<int> validated_channels;
   validated_channels.reserve(n_chan);

   if (channels.empty())
   {
      for (int i = 0; i < n_chan; i++)
         validated_channels.push_back(i);
   }
   else
   {
      for (auto& c : channels)
         if (c < n_chan)
            validated_channels.push_back(c);
   }

   if (n_chan_stride < validated_channels.size() || n_chan_stride == -1)
      n_chan_stride = validated_channels.size();
   
   return validated_channels;
}
