using Microsoft.AspNetCore.Mvc;

namespace dotnet_webapi.Controllers
{
    [ApiController]
    [Route("fibonacci")]
    public class FibonacciController : ControllerBase
    {
        [HttpGet]
        public ulong Get([FromQuery] int n) => Fibonacci(n);

        private ulong Fibonacci(int n)
        {
            if (n == 0) return 0;
            else if (n == 1) return 1;
            return Fibonacci(n - 2) + Fibonacci(n - 1);
        }

    }
}
