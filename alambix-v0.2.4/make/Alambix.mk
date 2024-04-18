# 
# Makefile that must be include into the makefile of an Alambic user projet.
#

LDWRAP = \
	-Wl,--wrap=sleep \
	-Wl,--wrap=usleep \
	-Wl,--wrap=nanosleep \
	-Wl,--wrap=fork \
	-Wl,--wrap=pthread_create \
	-Wl,--wrap=pthread_join \
	-Wl,--wrap=pthread_detach \
	-Wl,--wrap=pthread_cancel \
	-Wl,--wrap=pthread_mutex_lock \
	-Wl,--wrap=pthread_mutex_trylock \
	-Wl,--wrap=pthread_mutex_unlock \
	-Wl,--wrap=pthread_mutex_timedlock \
	-Wl,--wrap=pthread_cond_signal \
	-Wl,--wrap=pthread_cond_wait \
	-Wl,--wrap=pthread_cond_timedwait \
	-Wl,--wrap=pthread_barrier_init \
	-Wl,--wrap=pthread_barrier_destroy \
	-Wl,--wrap=pthread_barrier_wait \
	-Wl,--wrap=sem_wait \
	-Wl,--wrap=sem_timedwait \
	-Wl,--wrap=sem_post \
	-Wl,--wrap=timer_create \
	-Wl,--wrap=timer_delete \
	-Wl,--wrap=timer_settime \
	-Wl,--wrap=timer_gettime \
	-Wl,--wrap=popen \
	-Wl,--wrap=pclose \
	-Wl,--wrap=execv \
	-Wl,--wrap=execvp \
	-Wl,--wrap=execvpe \
	-Wl,--wrap=execve \
	-Wl,--wrap=mq_open \
	-Wl,--wrap=mq_close \
	-Wl,--wrap=mq_unlink \
	-Wl,--wrap=mq_send \
	-Wl,--wrap=mq_timedsend \
	-Wl,--wrap=mq_receive \
	-Wl,--wrap=mq_timedreceive \
	-Wl,--wrap=main \
	-Wl,--wrap=_alambix_open \
	-Wl,--wrap=alambix_close \
	-Wl,--wrap=alambix_choose_drink \
	-Wl,--wrap=alambix_order_drink \
	-Wl,--wrap=alambix_take_order \
	-Wl,--wrap=alambix_get_ordered_drink \
	-Wl,--wrap=alambix_has_ordered_drink \
	-Wl,--wrap=alambix_still_start \
	-Wl,--wrap=alambix_still_stop \
	-Wl,--wrap=alambix_provide_order \
	-Wl,--wrap=alambix_serve_order \


CCFLAGS  = -I$(ALAMBIX_PATH)/include/
CCFLAGS += -DALAMBIXUI="$(ALAMBIX_DIR)/ui/$(ALAMBIX_UI)/"

LDFLAGS  = -L$(ALAMBIX_PATH)/lib/ -lalambix -lm -lrt
LDFLAGS += $(LDWRAP)
LDFLAGS += `pkg-config --libs gtk+-3.0` `pkg-config --libs gmodule-2.0` `pkg-config --libs x11`

