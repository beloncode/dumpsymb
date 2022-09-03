#include <stdio.h>
#include <assert.h>

#include <bin/binary.h>

int main(int argc, char *argv[])
{
	if (argc < 2)
		return argc;

	BinCtx_t ctx;
	BinError_t err;

	bin_load_file(argv[1], &ctx);

	err = bin_get_last_error(&ctx);

	if (err != BIN_E_OK)
	{
		return fprintf(stderr, "Something wrong has happen: %s\n", bin_error_to_str(err));
	}

	/* Assert test */
	assert(err == bin_get_last_error(&ctx));

	bin_parser(&ctx);

	err = bin_get_last_error(&ctx);
	
	if (err != BIN_E_OK)
	{
		return fprintf(stderr, "Something wrong has happen: %s\n", bin_error_to_str(err));
	}

	printf("%s was been opened for parser\n", bin_get_filename(&ctx));

	printf("Binary size: %ld\n", bin_get_obj_size(&ctx));

	printf("Binary type is: %s\n", 
		bin_obj_type_to_str(bin_get_obj_type(&ctx))
	);

	/* bin_unload call isn't required */
	bin_finish(&ctx);

	return err;
}

