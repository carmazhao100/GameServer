define BUILD_LIBRARY
@$(if $(wildcard ar.mac),@$(RM) ar.mac)
@$(ECHO) CREATE $@ > ar.mac
@$(ECHO) SAVE >> ar.mac
@$(ECHO) END >> ar.mac
@$(AR) -M < ar.mac


@$(if $(filter %.a, $^),
@$(ECHO) OPEN $@ > ar.mac
@$(foreach LIB, $(filter %.a, $^),
@echo ADDLIB $(LIB) >> ar.mac
@)
@$(if $(filter %.o,$^),$(AR) -q $@ $(filter %.o, $^))


@$(ECHO) SAVE >> ar.mac
@$(ECHO) END >> ar.mac
@$(AR) -M $@ < ar.mac
@$(RM) ar.mac
)
endef
