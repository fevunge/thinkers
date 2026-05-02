//*fevunge */ ** */
//******* */ *** */
//****** */ **** */
//***** */ ***** */
//**** */ ****** */
//*** */ ******* */
//** */ ******** */
//* */ thinkers  */ 

#include "thinker.h"

int	main(int argc, char const *argv[])
{
	t_dinner	dinner;

	dinner.args = get_args(argc, argv);
	mise_en_place(&dinner);
	call_philos_to_dinner(&dinner);
	start_dinner(&dinner);
	finish_dinner(&dinner);
	return (0);
}
