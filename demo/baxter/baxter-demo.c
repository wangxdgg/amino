/* -*- mode: C; c-basic-offset: 4; -*- */
/* ex: set shiftwidth=4 tabstop=4 expandtab: */
/*
 * Copyright (c) 2015, Rice University
 * All rights reserved.
 *
 * Author(s): Neil T. Dantam <ntd@rice.edu>
 *
 *   Redistribution and use in source and binary forms, with or
 *   without modification, are permitted provided that the following
 *   conditions are met:
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/or other materials provided
 *     with the distribution.
 *   * Neither the name of copyright holder the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 *   CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 *   INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *   MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 *   USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 *   AND ON ANY HEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *   LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *   ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *   POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <error.h>
#include <stdio.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL.h>

#include "amino.h"
#include "amino/rx/rxtype.h"
#include "amino/rx/scenegraph.h"
#include "amino/rx/scene_gl.h"
#include "amino/rx/scene_sdl.h"

#include "baxter-demo.h"

void baxter_demo_setup_window( struct aa_rx_sg *scenegraph,
                               SDL_Window **window,
                               SDL_GLContext *gContext,
                               struct aa_gl_globals **globals )
{

    aa_sdl_gl_window( "SDL Test",
                      SDL_WINDOWPOS_UNDEFINED,
                      SDL_WINDOWPOS_UNDEFINED,
                      SCREEN_WIDTH,
                      SCREEN_HEIGHT,
                      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE,
                      window, gContext);

    printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
    aa_rx_sg_gl_init(scenegraph);

    // Initialize globals
    *globals = aa_gl_globals_create();
    // global camera
    {
        double world_E_camera_home[7] = AA_TF_QUTR_IDENT_INITIALIZER;
        double eye[3] = {3,2,1.25};
        double target[3] = {0,0,0};
        double up[3] = {0,0,1};
        aa_tf_qutr_mzlook( eye, target, up, world_E_camera_home );
        aa_gl_globals_set_camera_home( *globals, world_E_camera_home );
        aa_gl_globals_home_camera( *globals );

    }

    // global lighting
    {
        double v_light[3] = {.5,1,5};
        double ambient[3] = {.1,.1,.1};
        aa_gl_globals_set_light_position( *globals, v_light );
        aa_gl_globals_set_ambient(*globals, ambient);
    }

}