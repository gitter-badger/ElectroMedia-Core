#include "stdafx.h"
#include "Constants.h"
#include "MP3toData.h"
#include "CoreMath.h"
#include <sstream>

extern "C" 
{
#include "Dependencies\FFMPEG\libavcodec\avcodec.h"
#include "Dependencies\FFMPEG\libavformat\avformat.h"
#include "Dependencies\FFMPEG\libswscale\swscale.h"
}

// THIS FILE IS DEDICATED TO WORKING WITH FFTW3

#define INBUF_SIZE 4096
#define AUDIO_INBUF_SIZE 20480
#define AUDIO_REFILL_THRESH 4096

#pragma comment(lib, "dependencies\\lib\\avcodec.lib")

// This is the primary decoding mechanism. DubstepCannon.cpp calls this function to invoke
// several functions from FFMPEG.
FFmpegReturnValue DecodeMusic()
{
    auto audio_stream = -1;
	auto name = EmcSettings::GetInstance().song_filename_;
	auto mpeg_filename = EmcSettings::GetInstance().configuration_directory_ + name + ".mp3";
	auto emc_filename = name + EmcSettings::GetInstance().kEmcFileExtension;

    AVCodec         *aCodec;
    AVPacket        avPkt;
    AVFrame         *decode_frame = av_frame_alloc();

    AVCodecContext  *aCodecCtxt;
    AVFormatContext *pFormatCtxt = NULL;

    av_register_all();  //Initialize CODEC
    avformat_network_init();
    av_init_packet (&avPkt);

    // open the file if it exists
	if (avformat_open_input(&pFormatCtxt, mpeg_filename.c_str(), NULL, NULL) != 0)
    { 
        CoreMath::Debug("No file found!\n");
		return FFmpegReturnValue::NoFileFound;
    }

    //Get Streams Info 
    if(avformat_find_stream_info (pFormatCtxt,NULL) < 0)
    { 
        return FFmpegReturnValue::NoStreamAvailable;
    }
    //Testing the transfer.
    AVStream *stream = NULL;

    //Find Audio Stream
	for (int i = 0; i < pFormatCtxt->nb_streams; i++)
	{
		if (pFormatCtxt->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
		{
			audio_stream = i;
		}
	}

	aCodecCtxt = pFormatCtxt->streams[audio_stream]->codec; // opening decoder   
	aCodec = avcodec_find_decoder(pFormatCtxt->streams[audio_stream]->codec->codec_id);

    if (!aCodec)
        return FFmpegReturnValue::NoCodec;

	if (avcodec_open2(aCodecCtxt, aCodec, NULL) != 0)
		return FFmpegReturnValue::CodecCannotBeOpened;

    auto cnt = 0;
    static uint8_t **audio_dst_data = NULL;
    static int       audio_dst_linesize;
    uint8_t inbuf[AUDIO_INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];
    FILE *f, *outfile;

	outfile = fopen(emc_filename.c_str(), "wb");
    if(!outfile)
    {
        av_free(aCodecCtxt);
        CoreMath::Debug("ERROR: No outfile! Exiting...");
		FFmpegReturnValue::NoOutputFileAvailable;
    }

    while(av_read_frame(pFormatCtxt, &avPkt) >= 0 )
    {
		if (avPkt.stream_index == audio_stream)
        {
            int check = 0; 
            int result = avcodec_decode_audio4 (aCodecCtxt, decode_frame, &check, &avPkt);
            fwrite(decode_frame->data[0],1, decode_frame->linesize[0], outfile);
        }
        av_free_packet(&avPkt);

        cnt++;
    }

    fclose(outfile);

    avcodec_close(aCodecCtxt);
    av_free(aCodecCtxt);
    return FFmpegReturnValue::Success;
}