define build_library
$(if $(wildcard $@),@rm $@)
$(if $(wildcard ar.mac),@rm ar.mac)
$(if $(filter %.a, $^),
@echo CREATE $@ > ar.mac
@echo SAVE >> ar.mac
@echo END >> ar.mac
@$(AR) -M < ar.mac
)
$(if $(filter %.o,$^),@$(AR) -q $@ $(filter %.o, $^))
$(if $(filter %.a, $^),
@echo OPEN $@ > ar.mac
$(foreach lib, $(filter %.a, $^),
@echo ADDLIB $(lib) >> ar.mac
)
@echo SAVE >> ar.mac
@echo END >> ar.mac
@$(AR) -M < ar.mac
@rm ar.mac
)
endef


define make_subdir
 @for subdir in $(SUBDIRS) ; do \
 ( cd $$subdir && make $1) \
 done;
endef

curren_dir = $(shell pwd)
sources_obj_path = $(curren_dir)/objs

sources_c_obj_0    = $(patsubst %.c, %.o, $(SOURCES_C))
sources_c_obj       = $(foreach file, $(notdir $(sources_c_obj_0)), $(sources_obj_path)/$(file))

sources_cpp_obj_0    = $(patsubst %.cpp, %.o, $(SOURCES_CPP))
sources_cpp_obj       = $(foreach file, $(notdir $(sources_cpp_obj_0)), $(sources_obj_path)/$(file))

sub_modules_libs = $(foreach subdir, $(SUBDIRS), $(addprefix $(curren_dir)/$(subdir)/objs/lib, $(addsuffix .a , $(subdir))))

target = $(sources_obj_path)/$(module_lib)

all: preparePath sub_module  $(target)


$(target): $(sources_c_obj) $(sources_cpp_obj) $(sub_modules_libs)
	$(build_library)	

preparePath:
	@if [ ! -d $(sources_obj_path) ]; then \
	mkdir $(sources_obj_path); fi
	
sub_module:
	$(call make_subdir , all)
	
clean_sub_module:
	$(call make_subdir , clean)

clean:clean_sub_module
	@rm -rf $(sources_obj_path)
	@rm -rf $(target)

$(sources_c_obj) : $(sources_obj_path)/%.o : %.c
	@echo $(CC) $<
	@$(CC) $(CFLAGS) $(CC_OPTS) $(INC) $(INC_LOCAL) -c $< -o $@
	
$(sources_cpp_obj) : $(sources_obj_path)/%.o : %.cpp
	@echo $(CPP) $<
	@$(CPP) $(CFLAGS) $(CPP_OPTS) $(INC) $(INC_LOCAL) -c $< -o $@
