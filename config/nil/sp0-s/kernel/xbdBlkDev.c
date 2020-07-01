/* xbdBlkDev.c - XBD / BLK_DEV Converter */

/*
 * Copyright 2005-2013, 2015-2017 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
-------------------- 
02x,22jan17,yjl  Clean warning (VXW6-86130)
02w,18may16,myt  fix issue that fsmNameInstall cannot correctly add a XBD driver
                 name of which length is equal to MAX_DEVNAME (VXW6-85215)
02v,21jul15,zly  fix VXW6-84213: Inadequate error code when writing timed out
02u,13nov08,zly  fix WIND00437392:Incorrect usage of the xbd_bd_service structure 
                 field in xbdBlkDev.c when using Direct BIO Handling 
02t,13dec12,zly  WIND00393208:xbd layer can not propagate error status if underlying
                 driver don`t set errno
02s,12dec12,xwu  Coverity issue of XBD. 
02r,06jul12,zly  WIND00291846:Return NULLDEV instead of truncate device name
                 when name length > MAX_DEVNAME.
02q,09mar12,zly  WIND00333093:concurrent access problem  in the xbdBlkDev.c 
                 WIND00344633:make tXbdService`s priority setting-back to customer`s
                 configuration (XBD_BLK_DEV_TASK_PRIORITY)
02p,30dec11,zly  WIND00217466: add a direct mode for xbd. 
02o,29dec11,zly  Fix defect WIND00280464, xbdBlkDevCreateSyncHandler() can
                 cause an orphan semaphore
02n,15aug11,zly  fix for WIND00201989:xbd priority inversion issue 
02m,02sep10,zly  Fixed WIND00221245. 
02l,01mar10,lxj  adapted new code which added in 6.8 for LP64
02k,21oct09,zly  fix for defect WIND155758:Initialize global variable
                 xbdBlkDevServTskPri to 50.
02j,24jul09,lyc  LP64 support
02i,30may08,hps  fix for defect WIND00122060
02h,08apr08,hps  fix for WIND00119330: apigen documentation error
02g,23jul07,jlk  WIND00096994, return errno, if set, for blk dev ioctl.
02f,07feb07,dee  Set geometry of block device to default if not set. 
                 WIND00057345, WIND00086299.
02e,15jan07,jlk  fixed problem with XBD_TEST ioctl command introduced by the 
         fix for defect WIND00085339.
02d,11jan07,jlk  fixed defect WIND00085339.
02c,12dec06,dcc  fixed defect WIND0070704:"xbdBlkDevCreate creates a task with  
                 hardcoded priority."
02b,01mar06,dee  SPR# 118330, fix potential NULL pointer reference
         in xbdBlkDevCreateSync()
02a,30jan06,pcm  fixed GNU compiler warnings
01z,13sep05,dcc  fixed xbdBlkDevCreateSyncHandler unregistration on the wrong
         event (SPR 112091).
01y,31aug05,pcm  fixed documentation for xbdBlkDevCreateSync()
01x,29aug05,pcm  made removal event asynchronous
01w,25aug05,pcm  added support for xbd stack complete
01v,25aug05,jlk  Fixed media insertion detection on creation. Clean-up
01u,18aug05,rfr  Changed EAGAIN errno to S_ioLib_MEDIA_CHANGED
01t,17aug05,rfr  Changed to use zero-size XBD feature
01s,15jul05,jlk  added ability to delete XBD block wrapper
01r,04jul05,pcm  added comments and sections for doc build
01q,01jul05,rfr  Added Geometry and Basename ioctl commands
01p,21jun05,act  Oops, supposed to be primary insert on reinjection
01o,20jun05,act  add XBD eject ioctls
01n,16jun05,jlk  updated ioctl to return ENOTSUP when ioctl command isn't 
                 recognized
01m,14jun05,jlk  xbdBlkDevCreate() checks error code from bd_statusChk.
01l,14jun05,jlk  updated for erf changes.
01k,02jun05,jlk  xbd_bd_service() now checks return code from bd_statusChk and 
                 assumes media ejected if error code is not OK.
01j,12may05,jlk  Fixed race condition in xbdBlkDevCreate(). 
                 Updated copyright info.
01i,15apr05,rfr  Added support for removable devices
01h,11apr05,rfr  Using bio_bcount instead of bio_resid.
01g,08apr05,rfr  Fixed block number checking
01f,08apr05,rfr  Fixed setting of bio_resid when the underlying block dev
                 errors.
01e,25mar05,rfr  Adapted to changes in xbd.h
01d,08mar05,pcm  added library initialization routine
01c,10feb05,rfr  Changed block_t to sector_t
01b,27jan05,rfr  Moved Read and Write operations to the Service routine
01a,24jan05,rfr  Excluded a taskSpawn which does nothing
*/

/*
DESCRIPTION
This library contains routines for wrapping an XBD around a BLK_DEV.

INCLUDE FILES: xbdBlkDev.h
*/

/* includes */

#include <stdlib.h>
#include <string.h>
#include <vxWorks.h>
#include <errno.h>
#include <string.h>
#include <semLib.h>
#include <sysLib.h>
#include <taskLib.h>
#include <ioLib.h>
#include <xbdBlkDev.h>
#include <drv/erf/erfLib.h>

/* typedefs */

struct xbdBlkDev
    {
    XBD           xbd_bd_xbd;      /* XBD or device */
    SEM_ID        xbd_bd_mutex;    /* lock for this Wrapper */
    TASK_ID       xbd_bd_service;  /* Service task for this wrapper */
    SEM_ID        xbd_bd_ready;    /* Work available for service */
    BLK_DEV *     xbd_bd_dev;      /* Block Device that we wrap */
    int           xbd_bd_inserted; /* We are in the "inserted" state */
    devname_t     xbd_name;        /* The name of this XBD */
    struct bio *  xbd_bd_queueh;   /* List of bio's for us to process */
    struct bio *  xbd_bd_queuet;   /* Tail of the bio list */
    BOOL          xbd_instantiated;  /* TRUE if stack init is complete */
    SEM_ID        xbd_semId;       /* used for xbdBlkDevCreateSync() */
    int           xbd_bd_servTskPri; /* Service task priority*/ 
    };

/* foward declarations */

LOCAL int xbd_bd_ioctl        (struct xbd *, int, void *);
LOCAL int xbd_bd_strategy     (struct xbd *, struct bio *);
LOCAL int xbd_bd_dump         (struct xbd *, sector_t, void *, size_t);
LOCAL int xbd_bd_service      (struct xbdBlkDev *);
LOCAL int xbd_bd_test         (struct xbdBlkDev *);
LOCAL int xbd_bd_eject        (struct xbdBlkDev *);
LOCAL int xbd_bd_media_detect (BLK_DEV *);
LOCAL void xbdBlkDevCreateSyncHandler (UINT16, UINT16, void *, void *);
LOCAL int get_highest_bio_prio(struct xbdBlkDev *xbd_bd);
/* locals */

LOCAL struct xbd_funcs xbd_bd_funcs =
{
    xbd_bd_ioctl,
    xbd_bd_strategy,
    xbd_bd_dump,
};

#ifndef XBD_SERVICE_TASK_DEFAULT_PRIORITY
    #define XBD_SERVICE_TASK_DEFAULT_PRIORITY 200
#endif

LOCAL BOOL xbdBlkDevDirectBIOHandling;

/* globals */

int xbdBlkDevServTskPri = XBD_SERVICE_TASK_DEFAULT_PRIORITY;

/***************************************************************************
*
* xbdBlkDevLibInit - initialize the XBD block device wrapper
*
* This routine initializes the XBD block device wrapper.
*
* RETURNS: OK
*
* ERRNO: N/A
*/

STATUS xbdBlkDevLibInit
    (
    int xbdServiceTskPri,
    BOOL directMode
    )
    {
    xbdBlkDevServTskPri = xbdServiceTskPri;
    xbdBlkDevDirectBIOHandling = directMode;
    return(OK);
    }

/***************************************************************************
*
* xbdBlkDevCreate - create an XBD block device wrapper
*
* This routine creates an XBD block device wrapper.
*
* RETURNS: a device identifier upon success, or NULLDEV otherwise
*
* ERRNO: EINVAL 
*/

device_t xbdBlkDevCreate
    (
    BLK_DEV *     bd,       /* pointer to block device */
    const char *  name      /* pointer to device name  */
    )
    {
    struct xbdBlkDev *  xbd_bd;
    device_t            retVal;
    int                 error;
    long                erfParam;

    if ((name == NULL) || (name[0] == EOS) || (strlen(name) > sizeof(devname_t)))
        {
        errno = EINVAL;
        return(NULLDEV);
        }

    xbd_bd = malloc (sizeof (*xbd_bd));
    if (xbd_bd == NULL)
        goto error_malloc;

    xbd_bd->xbd_bd_mutex = semMCreate (SEM_Q_PRIORITY | SEM_INVERSION_SAFE);
    if (xbd_bd->xbd_bd_mutex == NULL)
        goto error_sem;

    xbd_bd->xbd_bd_ready = semBCreate(SEM_Q_PRIORITY, SEM_EMPTY);
    if (xbd_bd->xbd_bd_ready == NULL)
        goto error_count;

    xbd_bd->xbd_semId = semBCreate (SEM_Q_PRIORITY, SEM_EMPTY);
    if (xbd_bd->xbd_semId == NULL)
        goto error_bin_sem;

    /* Cache the name for when insertion events happen */
    strncpy(xbd_bd->xbd_name, name, MAX_DEVNAME);
    xbd_bd->xbd_name[MAX_DEVNAME] = '\0';
   
    xbd_bd->xbd_bd_queueh = NULL;
    xbd_bd->xbd_bd_queuet = NULL;
    xbd_bd->xbd_bd_dev    = bd;
    xbd_bd->xbd_instantiated    = FALSE;
    xbd_bd->xbd_bd_servTskPri = xbdBlkDevServTskPri;

    if (erfHandlerRegister (xbdEventCategory, xbdEventInstantiated,
                            xbdBlkDevCreateSyncHandler, xbd_bd, 0) != OK)
        {
        goto error_handler_failed;
        }

    if (!xbdBlkDevDirectBIOHandling)
        {
        /* Direct mode does not need this service task */

        xbd_bd->xbd_bd_service = taskSpawn ("tXbdService", xbd_bd->xbd_bd_servTskPri, 0,
                                            (size_t)65536, /* Stack size. */
                                            xbd_bd_service, (_Vx_usr_arg_t) xbd_bd,
                                            (_Vx_usr_arg_t)0, (_Vx_usr_arg_t)0, 
                                            (_Vx_usr_arg_t)0, (_Vx_usr_arg_t)0, 
                                            (_Vx_usr_arg_t)0, (_Vx_usr_arg_t)0, 
                                            (_Vx_usr_arg_t)0, (_Vx_usr_arg_t)0, 
                                            (_Vx_usr_arg_t)0);

        if (xbd_bd->xbd_bd_service == TASK_ID_ERROR)
            goto error_task;
        }
    /* Now test to see if we insert */
    bd->bd_readyChanged = 0;
    xbd_bd->xbd_bd_inserted = 0;

    xbd_bd->xbd_bd_inserted = xbd_bd_media_detect (bd);

    if (xbd_bd->xbd_bd_inserted)
        {
        error = xbdAttach ((struct xbd *) xbd_bd, &xbd_bd_funcs, name,
                           (unsigned)bd->bd_bytesPerBlk, (sector_t)bd->bd_nBlocks, &retVal);
        }
    else
        {
        error = xbdAttach ((struct xbd *) xbd_bd, &xbd_bd_funcs, name,
                           512, (sector_t)0, &retVal);
        }

    erfParam = retVal;
    if (error == 0)
        {
        erfEventRaise (xbdEventCategory, xbdEventPrimaryInsert,
                       ERF_ASYNC_PROC, (void *)erfParam, NULL);
        return(retVal);
        }

    error_task:
    error_handler_failed:
    semDelete (xbd_bd->xbd_semId);

    error_bin_sem:
    semDelete (xbd_bd->xbd_bd_ready);

    error_count:
    semDelete (xbd_bd->xbd_bd_mutex);

    error_sem:
    free (xbd_bd);

    error_malloc:
    return(NULLDEV);
    }


/***************************************************************************
*
* getNextBio - get the next bio
*
* /NOMANUAL
*/

LOCAL struct bio * getNextBio
    (
    struct xbdBlkDev *  xbd_bd   /* pointer to xbd block device wrapper */
    )
    {
    struct bio *  retVal;

    retVal = xbd_bd->xbd_bd_queueh;
    if (retVal != NULL)
        {
        xbd_bd->xbd_bd_queueh = retVal->bio_chain;
        retVal->bio_chain = NULL;

        if (xbd_bd->xbd_bd_queueh == NULL)
            xbd_bd->xbd_bd_queuet = NULL;
        }

    return(retVal);
    }

/***************************************************************************
*
* execBio - the execBio routine
*
* /NOMANUAL
*/

LOCAL void execBio
    (
    struct xbdBlkDev *  xbd_bd,   /* pointer to XBD block device wrapper */
    struct bio *        bio       /* pointer to bio */
    )
    {
    int        status = ERROR;
    unsigned   bd_bsize = xbd_bd->xbd_bd_xbd.xbd_blocksize;
    sector_t   bd_blocks = xbd_bd->xbd_bd_xbd.xbd_nblocks;
    sector_t   nblocks;
    BLK_DEV *  bd = xbd_bd->xbd_bd_dev;
    unsigned   size;

    /* Check that all of this transaction fits in the disk */
    size = bio->bio_bcount;
    nblocks = size / bd_bsize;

    /* If our starting block number is bad, done with error */
    if (bd_blocks <= bio->bio_blkno)
        {
        bio->bio_bcount = 0;
        bio_done (bio, ENOSPC);
        return;
        }

    /* If we overrun the end of the disk, truncate the block number */
    if (bd_blocks < bio->bio_blkno + nblocks)
        {
        nblocks = bd_blocks - bio->bio_blkno;
        }

    /* calculate the real size and residual */
    size = (unsigned int)nblocks * bd_bsize;
    bio->bio_bcount = size;

    /* If we have less than 1 block, set the resid and done it */
    if (nblocks == 0)
        {
        bio->bio_bcount = 0;
        bio_done (bio, 0);
        return;
        }


    if (bio->bio_flags & BIO_READ)
        {
        status = bd->bd_blkRd (bd, (int) bio->bio_blkno,
                               (int) nblocks, bio->bio_data);
        }
    else if (bio->bio_flags & BIO_WRITE)
        {
        status = bd->bd_blkWrt (bd, (int)bio->bio_blkno,
                                (int) nblocks, bio->bio_data);
        }
    if (status == OK)
        bio_done (bio, 0);
    else
        {
        bio->bio_bcount = 0;
        
        if (errno == 0)
            {
            bio_done (bio, EIO);
            }    
        /* S_ioLib_DISK_NOT_PRESENT is *really* ENXIO */
        else if (errno == S_ioLib_DISK_NOT_PRESENT)
            {
            bio_done (bio, ENXIO);
            /* The underlying media has gone away - remove this device */
            }
        else
            {
            bio_done (bio, errno);
            }
        }
    }


/***************************************************************************
*
* xbd_bd_service - XBD block device service routine
*
* /NOMANUAL
*/

LOCAL int xbd_bd_service
    (
    struct xbdBlkDev *  xbd_bd   /* pointer to XBD block device wrapper */
    )
    {
    STATUS        error;
    int           highest_prio;
    struct bio *  bio;
    SEM_ID        rdySem = xbd_bd->xbd_bd_ready;

    for (;;)
        {

        error = semTake (rdySem, WAIT_FOREVER);

        if (error == OK)
            {
            while (1)
                {
                semTake (xbd_bd->xbd_bd_mutex, WAIT_FOREVER);
                highest_prio = get_highest_bio_prio(xbd_bd);

                /* if service task priority is high */
                if ( xbd_bd->xbd_bd_servTskPri < highest_prio)
                    {
                    xbd_bd->xbd_bd_servTskPri = highest_prio;

                    /* lower service task prio based on left BIOs */

                    (void)taskPrioritySet(0, highest_prio);
                    }

                bio = getNextBio (xbd_bd);
                semGive (xbd_bd->xbd_bd_mutex);

                if (bio!= NULL)
                    execBio (xbd_bd, bio);
                else
                    break;
                }
            }
        else
            {
            /* 
            * We're probably being deleted or something is corrupted. 
            * Either case commit suicide .
            */
            return ERROR;
            }
        }
    }


/***************************************************************************
*
* xbd_bd_ioctl - XBD block device ioctl routine
*
* /NOMANUAL
*/

LOCAL int xbd_bd_ioctl
    (
    struct xbd *  self,
    int           command, 
    void *        arg
    )
    {
    struct xbdBlkDev *  xbd_bd = (struct xbdBlkDev *) self;
    device_t            dev;
    UINT16              reType;
    BLK_DEV *           bd = xbd_bd->xbd_bd_dev;
    XBD_GEOMETRY *      geo;
    int                 status;
    unsigned int        uCommand;
    long                erfParam;

    /* Test to see if we have been removed */
    status = xbd_bd_test(xbd_bd);
    if (xbd_bd->xbd_bd_inserted)
        {
        /* We are a full-size XBD - if there is no media, then eject */
        if (status == ERROR)
            {
            /* Removal happened */
            xbd_bd_eject(xbd_bd);
            return(S_ioLib_MEDIA_CHANGED);
            }
        }
    else
        {
        /* We are a 0 size XBD - if there IS media then eject */
        if (status == ERROR)
            {
            status = xbd_bd_test(xbd_bd);
            if (status == OK)
                {

                xbd_bd_eject(xbd_bd);
                return(S_ioLib_MEDIA_CHANGED);
                }
            }
        }


    uCommand = (unsigned int)command;

    switch (uCommand)
        {
        case XBD_TEST:
            return(OK);

        case XBD_SOFT_EJECT:
        case XBD_HARD_EJECT:
            /* we are the base XBD so if we get these it is for us */
            erfParam = (long) xbd_bd->xbd_bd_xbd.xbd_dev.dv_dev;
            erfEventRaise (xbdEventCategory, xbdEventRemove, ERF_ASYNC_PROC,
                           (void *)erfParam, NULL);
            reType = (UINT16)((uCommand == XBD_HARD_EJECT) ?
                              xbdEventPrimaryInsert : xbdEventSoftInsert);
            erfEventRaise (xbdEventCategory, reType, ERF_ASYNC_PROC,
                           (void *)erfParam, NULL);
            return(0);

        case XBD_GETGEOMETRY:
            geo = (XBD_GEOMETRY *) arg;

            /* if the block driver didn't set values for sectors/track and number
             * of heads, use defaults for calculation of number of cylinders.
             */
            if (bd->bd_nHeads == 0)
                geo->heads = DEFAULT_HEADS;
            else
                geo->heads = (unsigned int)bd->bd_nHeads;
            if (bd->bd_blksPerTrack == 0)
                geo->secs_per_track = DEFAULT_SECS_TRACK;
            else
                geo->secs_per_track = (unsigned int)bd->bd_blksPerTrack;

            geo->total_blocks = (sector_t)bd->bd_nBlocks;
            geo->blocksize = (unsigned int)bd->bd_bytesPerBlk;
            geo->cylinders = geo->blocksize / geo->secs_per_track / geo->heads;
            return(0);

        case XBD_GETBASENAME:
            dev = xbd_bd->xbd_bd_xbd.xbd_dev.dv_dev;
            if (devName(dev, arg) == ERROR)
                return errno;
            else
                return(0);

        case XBD_SYNC:
            if (bd->bd_ioctl)
                bd->bd_ioctl(bd, FIOSYNC, 0);
            return(0);

        case XBD_STACK_COMPLETE:
            if (!xbd_bd->xbd_instantiated)
                {
                erfEventRaise (xbdEventCategory, xbdEventInstantiated,
                               ERF_ASYNC_PROC,
                               xbd_bd->xbd_bd_xbd.xbd_dev.dv_xname, NULL);
                xbd_bd->xbd_instantiated = TRUE;
                }
            return(OK);

        default:
            if (bd->bd_ioctl)
                {
                if (bd->bd_ioctl(bd, command, arg) != OK)
                    {
                    if (errno != OK)
                        return(errno);
                    }
                else
                    return(OK);
                }
            return(ENOTSUP);
        }
    }

/***************************************************************************
*
* xbd_bd_strategy - XBD block device strategy routine
*
* /NOMANUAL
*/

LOCAL int xbd_bd_strategy
    (
    struct xbd *  self,       /* pointer to XBD */
    struct bio *  bio         /* pointer to bio */
    )
    {
    struct xbdBlkDev * xbd_bd = (struct xbdBlkDev *) self;
    int                status;
    struct bio *       next_bio;


    /* Test to see if we have been removed */
    status = xbd_bd_test(xbd_bd);
    if (xbd_bd->xbd_bd_inserted)
        {
        /* We are a full-size XBD - if there is no media, then eject */
        if (status == ERROR)
            {
            /* Removal happened */
            xbd_bd_eject(xbd_bd);
            bio_done(bio, S_ioLib_MEDIA_CHANGED);
            return(S_ioLib_MEDIA_CHANGED);
            }
        }
    else
        {
        /* We are a 0 size XBD - if there IS media then eject */
        if (status == ERROR)
            {
            status = xbd_bd_test(xbd_bd);
            if (status == OK)
                {

                xbd_bd_eject(xbd_bd);
                bio_done(bio, S_ioLib_MEDIA_CHANGED);
                return(S_ioLib_MEDIA_CHANGED);
                }

            }
        }

    if (semTake (xbd_bd->xbd_bd_mutex, WAIT_FOREVER) != OK)
        return errno;

    /* if service task priority is low */
    if ((xbdBlkDevDirectBIOHandling == FALSE) &&
        (xbd_bd->xbd_bd_servTskPri > bio->bio_priority))
        {
        xbd_bd->xbd_bd_servTskPri = bio->bio_priority;
        /* raise service task priority */
        (void) taskPrioritySet(xbd_bd->xbd_bd_service, bio->bio_priority);
        }


    /* 
 * Direct Mode 
 * Call the block read/write function for this BIO directly
*/
    if (xbdBlkDevDirectBIOHandling)
        {
        execBio(xbd_bd, bio);
        }
    else
        {
        /* Iterate through the chain, running each bio as we get it */
        for ( ; bio != NULL; bio = next_bio)
            {
            /* Make sure that we can get the next one */
            next_bio = bio->bio_chain;


            /* Add this bio as the tail of the queue */
            bio->bio_chain = NULL;

            if (xbd_bd->xbd_bd_queuet)
                {
                xbd_bd->xbd_bd_queuet->bio_chain = bio;
                }
            else
                {
                xbd_bd->xbd_bd_queueh = bio;
                }
            xbd_bd->xbd_bd_queuet = bio;
            }
        /* Tap our service task */
        semGive (xbd_bd->xbd_bd_ready);
        }
    semGive (xbd_bd->xbd_bd_mutex);
    return(OK);
    }

/***************************************************************************
*
* xbd_bd_dump - XBD block device dump routine
*
* /NOMANUAL
*/

LOCAL int xbd_bd_dump
    (
    struct xbd *  self, 
    sector_t      blkno, 
    void *        data, 
    size_t        size
    )
    {
    return(EINVAL);
    }

/***************************************************************************
*
* xbdBlkDevDelete - deletes an XBD block device wrapper
*
* This routine deletes or destroys an XBD block device wrapper.
*
* The <d> parameter specifies the XBD block wrapper to delete. This should be 
* the same value that was returned from xbdBlkDevCreate()
*
* The <ppbd> parameter is an out parameter that can be used to return the block
* device pointer used in xbdBlkDevCreate(). If specified as NULL no attempt to
* return the block device pointer is attempted.
*
* RETURNS: a device identifier upon success, or NULLDEV otherwise
*
* ERRNO: 
*/

STATUS xbdBlkDevDelete
    (
    device_t     dev, /* device_t returned from xbdBlkDevCreate */
    BLK_DEV **   ppbd /* pointer to block device pointer */
    )
    {
    struct xbdBlkDev *  xbd_bd;
    struct bio * bio;
    long   erfParam;

    xbd_bd = (struct xbdBlkDev *) devMap (dev);

    if (xbd_bd == NULL)
        return(ERROR);

    /* Grab the semaphore */
    semTake (xbd_bd->xbd_bd_mutex, WAIT_FOREVER);

#ifndef _WRS_CONFIG_OBJECT_VERIFICATION
    /* 
    * Without the selection of OBJECT_VERIFICATION, WIND objects passed to VxWorks kernel APIs, 
    * such as semTake() and semGive(), will not be validated. If we want to remove the overhead
    * of the validation from the kernel APIs, we must ensure a system where objects are not deleted. 
    * 
    * Delete the service task, prevent it from accessing deleted resources. (WIND00221245)
    */

    if (xbdBlkDevDirectBIOHandling == FALSE)
        taskDelete(xbd_bd->xbd_bd_service);
#else
    /* Delete the semaphore and wait for the service task to die */
    semDelete (xbd_bd->xbd_bd_ready);
    taskDelay (sysClkRateGet ());
#endif

    /* Detach the XBD so no one else can access it */
    xbdDetach (&xbd_bd->xbd_bd_xbd);
    devUnmap ((struct device *)xbd_bd);

    /* Drain the bios */
    bio = getNextBio (xbd_bd);
    while (bio)
        {
        bio_done (bio, ENXIO);
        bio = getNextBio (xbd_bd);
        }

    /* 
    * Return the blkdev wrapper was instantiated on so the caller can do 
    * additional clean-up 
    */
    if (ppbd)
        *ppbd = xbd_bd->xbd_bd_dev;

    /* Free all resources */
#ifndef _WRS_CONFIG_OBJECT_VERIFICATION
    semDelete (xbd_bd->xbd_bd_ready);
#endif
    semDelete (xbd_bd->xbd_semId);
    semDelete (xbd_bd->xbd_bd_mutex);
    xbd_bd->xbd_bd_mutex = NULL;
    xbd_bd->xbd_bd_ready = NULL;
    free (xbd_bd);

    /* Finally send a removal event to whatever maybe on top of us */
    erfParam = (long) dev;
    erfEventRaise(xbdEventCategory, xbdEventRemove, 
                  ERF_SYNC_PROC, (void *)erfParam, NULL);

    return(OK);
    }


/***************************************************************************
* xbd_bd_test - Test a block wrapper for media existence
*
* /NOMANUAL
*/

LOCAL int xbd_bd_test
    (
    struct xbdBlkDev *xbd_bd
    )
    {
    BLK_DEV *  bd = xbd_bd->xbd_bd_dev;
    int error;
    int rc_bit;

    /* call the driver's status routine, if one exists */

    if (bd->bd_statusChk)
        error = bd->bd_statusChk(bd);
    else
        error = OK;

    rc_bit = bd->bd_readyChanged;
    bd->bd_readyChanged = 0;

    if (error != OK)
        return(ERROR);

    if (rc_bit != 0)
        {
        return(ERROR);
        }

    return(OK);
    }



/***************************************************************************
*
* xbd_bd_eject - Eject the device and instantiate the next step
*
* /NOMANUAL
*/

LOCAL int xbd_bd_eject
    (
    struct xbdBlkDev *xbd_bd
    )
    {
    int error;
    device_t device;
    BLK_DEV *  bd = xbd_bd->xbd_bd_dev;
    struct bio *bio;
    long   erfParam;

    /* Announce the ejection */
    erfParam = (long)xbd_bd->xbd_bd_xbd.xbd_dev.dv_dev;
    erfEventRaise(xbdEventCategory, xbdEventMediaChanged, ERF_ASYNC_PROC, 
                  (void *)erfParam, NULL);


    /* Detach the XBD handle */
    xbdDetach(&xbd_bd->xbd_bd_xbd);
    devUnmap(&xbd_bd->xbd_bd_xbd.xbd_dev);

    /* Done any pending bio's */
    semTake(xbd_bd->xbd_bd_mutex, WAIT_FOREVER);
    while ((bio = getNextBio(xbd_bd)))
        bio_done(bio, ENXIO);
    semGive(xbd_bd->xbd_bd_mutex);


    /* 
    * Now we instantiate the next XBD - if we have media, then its a regular XBB
    * but if we don't, its an xbd of size 0 which fills in for the XBD until media
    * is actually inserted
    */

    if (xbd_bd_test(xbd_bd) == OK)
        {
        /* We have new media to mount */
        error = xbdAttach ((struct xbd *) xbd_bd, &xbd_bd_funcs, xbd_bd->xbd_name,
                           (unsigned)bd->bd_bytesPerBlk, (sector_t)bd->bd_nBlocks, &device);

        xbd_bd->xbd_bd_inserted = 1;
        }
    else
        {
        /* We are making a 0-block length XBD */
        error = xbdAttach ((struct xbd *) xbd_bd, &xbd_bd_funcs, xbd_bd->xbd_name,
                           512, (sector_t)0, &device);
        xbd_bd->xbd_bd_inserted = 0;
        }

    /* Announce our new XBD */
    erfParam = (long)device;
    if (error == OK)
        {
        erfEventRaise(xbdEventCategory, xbdEventPrimaryInsert, 
                      ERF_ASYNC_PROC, (void *)erfParam, NULL);
        }

    return(error);
    }

/***************************************************************************
*
* xbd_bd_media_detect - Detects if media is present in drive.
*
* This function detects if media is present in the drive. It is called to
* set the initial state on device creation.
*
* /NOMANUAL
*/

LOCAL int xbd_bd_media_detect
    (
    BLK_DEV *     bd       /* pointer to block device */
    )
    {
    int error;

    if (!bd->bd_statusChk)
        {
        /* Assume media present */
        return 1;
        }

    error = bd->bd_statusChk(bd);
    if (error != OK)
        {
        /* No media present */
        return 0;
        }

    if (bd->bd_readyChanged == 0)
        {
        /* Media present */
        return 1;
        }

    bd->bd_readyChanged = 0;
    error = bd->bd_statusChk(bd);
    if (bd->bd_readyChanged == 0)
        {
        /* Media present */
        return 1;
        }

    /* No media present */
    return 0;
    }

/***************************************************************************
*
* xbdBlkDevCreateSyncHandler -
*/

LOCAL void xbdBlkDevCreateSyncHandler
    (
    UINT16 Category,
    UINT16 Type,
    void * eventData,
    void * userData
    )
    {
    struct xbdBlkDev *  pDev;
    devname_t *         devname;

    if ((Category == xbdEventCategory) && (Type == xbdEventInstantiated))
        {
        devname = (devname_t *) eventData;
        pDev = (struct xbdBlkDev *) userData;

        if (strncmp ((char*) devname,
                     (char *) pDev->xbd_bd_xbd.xbd_dev.dv_xname,
                     sizeof (devname_t)) != 0)
            {
            /* To call semGive or not to call semGive is OK, it is almost impossible
               that devname does not match */

            semGive(pDev->xbd_semId);
            return;
            }

        erfHandlerUnregister (xbdEventCategory, xbdEventInstantiated,
                              xbdBlkDevCreateSyncHandler, userData);

        semGive (pDev->xbd_semId);
        }

    return;
    }

/***************************************************************************
*
* xbdBlkDevCreateSync - synchronously create an XBD block device wrapper
*
* This routine creates an XBD block device wrapper.  It returns after the
* entire XBD stack has been created/initialized.
*
* RETURNS: a device identifier upon success, or NULLDEV otherwise
*
* ERRNO: 
*/

device_t xbdBlkDevCreateSync
    (
    BLK_DEV *     bd,       /* pointer to block device */
    const char *  name      /* pointer to device name  */
    )
    {
    device_t            xbd;
    struct xbdBlkDev *  pDev;

    xbd = xbdBlkDevCreate (bd, name);

    pDev = (struct xbdBlkDev *) devMap (xbd);
    if (pDev == NULL)
        return(NULLDEV);

    semTake (pDev->xbd_semId, WAIT_FOREVER);

    devUnmap ((struct device *) pDev);

    return(xbd);
    }

/***************************************************************************
* get_highest_bio_prio - Get the highest priority in the bio list.
*
* This routine get the highest priority of bio in the bio list.
*
* RETURNS: the highest priority.
*
* \NOMANUAL
*
* ERRNO:
*/


LOCAL int get_highest_bio_prio
    (
    struct xbdBlkDev *xbd_bd
    )
    {
    int minValue = xbdBlkDevServTskPri;
    struct bio *nextBio;

    if (NULL != xbd_bd->xbd_bd_queueh)
        {
        minValue = xbd_bd->xbd_bd_queueh->bio_priority;
        for (nextBio=xbd_bd->xbd_bd_queueh->bio_chain; nextBio!=NULL; nextBio=nextBio->bio_chain)
            {
            minValue = (minValue < nextBio->bio_priority) ? minValue:nextBio->bio_priority;
            }
        }

    return minValue;
    }
