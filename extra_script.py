Import("env")

# Read value from other environments
config = env.GetProjectConfig()
xsde_path = config.get("env", "xsde_path")
#extra_scripts = env.GetProjectOption("extra_scripts")
#xsde_path = env.GetProjectOption("xsde_path")

print (xsde_path)