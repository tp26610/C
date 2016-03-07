#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vorbis/codec.h"
#include "vorbis/vorbisfile.h"

#ifdef _WIN32
#include <io.h>
#include <fcntl.h>
#endif

char pcmout[4096];

int main(int argc, char **argv){

  OggVorbis_File vf;
  int eof=0;
  int current_section;

  FILE *in, *out;

  in = fopen("in.ogg", "rb");
  out = fopen("out.pcm", "wb");

  if(ov_open_callbacks(in, &vf, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
      printf("Input does not appear to be an Ogg bitstream.\n");
      exit(1);
  }

  {
     char **ptr=ov_comment(&vf,-1)->user_comments;
     vorbis_info *vi=ov_info(&vf,-1);
     while(*ptr){
       printf("%s\n",*ptr);
       ++ptr;
     }
     printf("\nBitstream is %d channel, %ldHz\n",vi->channels,vi->rate);
     printf("\nDecoded length: %ld samples\n",
             (long)ov_pcm_total(&vf,-1));
     printf("Encoded by: %s\n\n",ov_comment(&vf,-1)->vendor);
   }


  while(!eof){
    long ret=ov_read(&vf,pcmout,sizeof(pcmout),0,2,1,&current_section);
    if (ret == 0) {
      /* EOF */
      eof=1;
    } else if (ret < 0) {
      /* error in the stream.  Not a problem, just reporting it in
	 case we (the app) cares.  In this case, we don't. */
    } else {
      /* we don't bother dealing with sample rate changes, etc, but
	 you'll have to */
      fwrite(pcmout,1,ret,out);
    }
  }

  ov_clear(&vf);

  printf("Done.\n");
  return(0);
}
