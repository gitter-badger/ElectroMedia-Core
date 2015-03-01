#include "stdafx.h"
#include "MP3toData.h"
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
int decodeMusic(std::string directoryName, std::string songName)
{
    int audioStream = -1;
    std::string name = songName;
    std::string mpegFileName = directoryName + name + ".mp3";
    std::string emcFileName = name + EMC_FILE_EXTENSION;

    AVCodec         *aCodec;
    AVPacket        avPkt;
    AVFrame         *decode_frame = av_frame_alloc();

    AVCodecContext  *aCodecCtxt;
    AVFormatContext *pFormatCtxt = NULL;

    av_register_all();  //Initialize CODEC
    avformat_network_init();
    av_init_packet (&avPkt);

    // open the file if it exists
    if (avformat_open_input(&pFormatCtxt, mpegFileName.c_str(), NULL, NULL) != 0)
    { 
        _tprintf(_T("No file found!\n"));
        return -2;
    }

    //Get Streams Info 
    if(avformat_find_stream_info (pFormatCtxt,NULL) < 0)
    { 
        return -3; 
    }
    //Testing the transfer.
    AVStream *stream = NULL;

    //Find Audio Stream
    for (int i = 0;  i < pFormatCtxt->nb_streams ; i++) 
        if (pFormatCtxt->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
            audioStream = i;

    aCodecCtxt = pFormatCtxt ->streams [audioStream]->codec; // opening decoder   
    aCodec = avcodec_find_decoder( pFormatCtxt->streams [audioStream] ->codec->codec_id);

    if (!aCodec)
        return -8;

    if (avcodec_open2(aCodecCtxt,aCodec,NULL)!=0)
        return -9; 

    int cnt = 0;
    static uint8_t **audio_dst_data = NULL;
    static int       audio_dst_linesize;
    uint8_t inbuf[AUDIO_INBUF_SIZE + FF_INPUT_BUFFER_PADDING_SIZE];
    FILE *f, *outfile;

    outfile = fopen(emcFileName.c_str(), "wb");
    if(!outfile)
    {
        av_free(aCodecCtxt);
        debug("ERROR: No outfile! Exiting...");
        exit(1);
    }

    while(av_read_frame(pFormatCtxt, &avPkt) >= 0 )
    {
        if (avPkt.stream_index == audioStream)
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
    return 1;
}