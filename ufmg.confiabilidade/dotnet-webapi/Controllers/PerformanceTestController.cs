using Microsoft.AspNetCore.Mvc;

namespace dotnet_webapi.Controllers
{
    [ApiController]
    [Route("performance-test")]
    public class PerformanceTestController : ControllerBase
    {
        [HttpGet]
        public string Get() => "ok";
        
    }
}
